CC=g++
CFLAGS=-I/usr/include/SDL2 -O0 -g -std=c++11
LIBS=-lSDL2

all:hexmacros.o hex_blank hex_sizes hex_build

hex_blank:hex_blank.c hexmacros.o
	$(CC) $(CFLAGS) -o hex_blank hex_blank.c hexmacros.o

hex_sizes:hex_sizes.c hexmacros.o
	$(CC) $(CFLAGS) -o hex_sizes hex_sizes.c hexmacros.o

hex_build:hex_build.cpp hex_build.hpp hexmacros.o
	$(CC) $(CFLAGS) -o hex_build hex_build.cpp hexmacros.o

hexmacros.o:hexmacros.c hexmacros.h
	$(CC) $(CFLAGS) -c hexmacros.c



clean:
	rm -f hexmacros.o hex_blank hex_sizes hex_build
