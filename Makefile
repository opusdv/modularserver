CC=gcc
ARCHIVE=ar
RDIR=release
IDIR=include/server

SDIR=src
ODIR=obj

CFLAGS=-I$(IDIR)

_DEPS=connection.h config.h plugin.h coreserver.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ=config.o connection.o  plugin.o coreserver.o main.o 
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(RDIR)/$@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
	rm -f $(RDIR)/*

