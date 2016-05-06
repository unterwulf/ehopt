# This makefile is to be used with Turbo C 2.0.
# It won't work with Borland C++.

CC = tcc
CFLAGS = -w -mt

ehopt.com: ehopt.obj xstdio.obj
	$(CC) $(CFLAGS) -e$& -lt ehopt.obj xstdio.obj

.c.obj:
	$(CC) $(CFLAGS) -c $< 

clean:
	del *.obj
	del ehopt.com
