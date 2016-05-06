CFLAGS = -W -Wall -DHAVE_STDINT_H
OBJ = ehopt.o xstdio.o

ehopt: $(OBJ)

.PHONY: clean
clean:
	$(RM) ehopt $(OBJ)
