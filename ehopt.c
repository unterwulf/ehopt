#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

#if HAVE_STDINT_H
#include <stdint.h>
#else
#define uint16_t unsigned short
#endif

struct EXE {
	uint16_t signature; /* == 0x5a4D */
	uint16_t bytes_in_last_block;
	uint16_t blocks_in_file;
	uint16_t num_relocs;
	uint16_t header_paragraphs;
	uint16_t min_extra_paragraphs;
	uint16_t max_extra_paragraphs;
	uint16_t ss;
	uint16_t sp;
	uint16_t checksum;
	uint16_t ip;
	uint16_t cs;
	uint16_t reloc_table_offset;
	uint16_t overlay_number;
};

struct EXE_RELOC {
	uint16_t offset;
	uint16_t segment;
};

int main(int argc, char *argv[])
{
	FILE *in, *out;
	int ch;
	char *meta;
	size_t i, metalen = 0;
	struct EXE hdr, new_hdr;

	if (argc != 3 && argc != 4) {
		fprintf(stderr, "usage: ehopt in.exe out.exe [meta]\n");
		return EXIT_FAILURE;
	}

	in = xfopen(argv[1], "rb");

	xfread(&hdr, sizeof (struct EXE), 1, in);

	if (argc == 4) {
		meta = argv[3];
		metalen = strlen(meta);
	}

	new_hdr = hdr;
	new_hdr.reloc_table_offset = sizeof (struct EXE) + metalen;
	new_hdr.header_paragraphs = (new_hdr.reloc_table_offset
		+ sizeof (struct EXE_RELOC) * new_hdr.num_relocs + 15) >> 4;

	out = fopen(argv[2], "wb");
	xfwrite(&new_hdr, sizeof (struct EXE), 1, out);
	xfwrite(meta, metalen, 1, out);

	xfseek(in, hdr.reloc_table_offset, SEEK_SET);
	for (i = 0; i < hdr.num_relocs; i++) {
		struct EXE_RELOC reloc;
		xfread(&reloc, sizeof (struct EXE_RELOC), 1, in);
		xfwrite(&reloc, sizeof (struct EXE_RELOC), 1, out);
	}

	xfseek(in, hdr.header_paragraphs << 4, SEEK_SET);
	xfseek(out, new_hdr.header_paragraphs << 4, SEEK_SET);

	while ((ch = fgetc(in)) != EOF)
		xfputc(ch, out);

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}
