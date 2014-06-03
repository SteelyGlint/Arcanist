CC=clang++
INCLUDES=-I/usr/include/SDL2 -I.. -I. -I../util/ -g
#DFLAGS=-fprofile-arcs -ftest-coverage -g -pg -O0

CFLAGS=-O2 $(INCLUDES) $(DFLAGS) -std=c++11 -Wall #-pedantic -Werror
LIBS=-lSDL2 -lSDL2_image

.PHONY:test_motes test_display test_performance test_mote_pool test_hex

all:test_motes test_display test_performance test_mote_pool test_hex

test_motes:
	$(CC) $(CFLAGS) -o test_motes test_main.cpp test_sdl_motes.cpp ../MoteMovementManager.o ../GraphicalHexGrid.o ../HexCell.o $(LIBS)

test_display:
	$(CC) $(CFLAGS) -o test_display test_main.cpp test_sdl_geo.cpp ../HexCell.cpp $(LIBS)

test_performance:
	$(CC) $(CFLAGS) -o test_performance speed_test.cpp $(LIBS)

test_mote_pool:
	$(CC) $(CFLAGS) -o test_mote test_mote_pool.cpp

test_hex:
	$(CC) $(CFLAGS) -o test_hex test_hex_dim.cpp


clean:
	rm -rf test_performance
