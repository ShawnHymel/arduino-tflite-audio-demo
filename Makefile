WARNINGS=-W -Wall -Wstrict-prototypes -Wmissing-prototypes -Waggregate-return \
    -Wcast-align -Wcast-qual -Wnested-externs -Wshadow -Wbad-function-cast \
    -Wwrite-strings

#CFLAGS=-O3 -I./ext/kissfft -I./ext/kissfft/tools $(WARNINGS)
#CFLAGS+=-ffast-math -fomit-frame-pointer 
CFLAGS=-I./ext/kissfft -I./ext/kissfft/tools

CC = gcc

ODIR = ./bin
TDIR = ./test
EDIR = ./ext

DATATYPE = float

TYPEFLAGS = -DFIXED_POINT=16 
#TYPEFLAGS = -Dkiss_fft_scalar=$(DATATYPE)

SRCFILES = 	./ext/kissfft/kiss_fft.c \
			./ext/kissfft//tools/kiss_fftr.c

.PHONY: all
all: test_kissfft_stft

hello: hello
	$(CC) -o bin/hello test/hello.c

test_kissfft_real: test/test_kissfft_real.c $(SRCFILES)
	$(CC) -o bin/$@ $(CFLAGS) $(TYPEFLAGS) $+ -lm

test_kissfft_stft: test/test_kissfft_stft.c $(SRCFILES)
	$(CC) -o bin/$@ $(CFLAGS) $(TYPEFLAGS) $+ -lm

.PHONY: clean

clean:
	rm -f bin/*.o bin/*.exe