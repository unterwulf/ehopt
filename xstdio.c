#include <stdio.h>
#include <stdlib.h>

FILE *xfopen(const char *path, const char *mode)
{
    FILE *fp = fopen(path, mode);

    if (!fp) {
        fputs("unable to open file '", stderr);
        fputs(path, stderr);
        fputs("'\n", stderr);
        exit(EXIT_FAILURE);
    }

    return fp;
}

void xfread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (nmemb != fread(ptr, size, nmemb, stream)) {
        fputs("read error\n", stderr);
        exit(EXIT_FAILURE);
    }
}

void xfseek(FILE *stream, long offset, int whence)
{
    if (0 != fseek(stream, offset, whence)) {
        fputs("fseek error\n", stderr);
        exit(EXIT_FAILURE);
    }
}

void xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (nmemb != fwrite(ptr, size, nmemb, stream)) {
        fputs("write error\n", stderr);
        exit(EXIT_FAILURE);
    }
}

int xfgetc(FILE *stream)
{
    int c = fgetc(stream);

    if (c == EOF) {
        fputs("fgetc error\n", stderr);
        exit(EXIT_FAILURE);
    }

    return c;
}

void xfputc(int c, FILE *stream)
{
    if (EOF == fputc(c, stream)) {
        fputs("fputc error\n", stderr);
        exit(EXIT_FAILURE);
    }
}
