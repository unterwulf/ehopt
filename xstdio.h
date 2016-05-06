#ifndef XSTDIO_H
#define XSTDIO_H

#include <stddef.h>
#include <stdio.h>

extern FILE *xfopen(const char *path, const char *mode);
extern void xfread(void *ptr, size_t size, size_t nmemb, FILE *stream);
extern void xfseek(FILE *stream, long offset, int whence);
extern void xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

extern int xfgetc(FILE *stream);
extern void xfputc(int c, FILE *stream);

#endif /* XSTDIO_H */
