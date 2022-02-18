CC=gcc
ARCHIVE=ar
RDIR=release
IDIR=include/server

LDIR=lib
_LIB=libcoreserver.a
LIB=$(patsubst %, $(LDIR)/%, $(_LIB))

SDIR=src
ODIR=obj
LIBSFLAG=-lcoreserver
LIBSEARCHDIR=-L$(LDIR)
CFLAGS=-I$(IDIR)

_DEPS=core.h config.h plugin.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ=core.o config.o plugin.o main.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIB): $(OBJ)
	$(ARCHIVE) crs $@ $?

main: $(LIB)
	$(CC) -o $(RDIR)/$@ $(LIBSEARCHDIR)  $(CFLAGS)  $(LIBSFLAG)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
	rm -f $(LDIR)/*
	rm -f $(RDIR)/*

