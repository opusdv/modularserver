CC=gcc
RDIR=release
IDIR=include/server
LDIR=lib
SDIR=src
ODIR=obj
#LIBS=-lcore -lconfig
CFLAGS=-I$(IDIR)
_DEPS=core.h config.h plugin.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))
_OBJ=core.o config.o plugin.o main.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(RDIR)/$@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o


