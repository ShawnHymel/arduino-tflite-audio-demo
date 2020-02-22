CC = gcc

ODIR = ./bin
TDIR = ./test
EDIR = ./ext

.PHONY: all
all: hello

hello: hello
	$(CC) -o bin/hello test/hello.c

.PHONY: clean

clean:
	rm -f bin/*.o bin/*.exe