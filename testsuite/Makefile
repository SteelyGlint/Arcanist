CC=g++
INCLUDES=-I/usr/include/SDL2 -I.. -I. -Iutil/
CFLAGS=-O2 -g $(INCLUDES) -std=c++11 -Wall #-pedantic -Werror
LIBS=-lSDL2 -lSDL2_image

.PHONY:test_display test_performance

test_display:
	$(CC) $(CFLAGS) -o test_display test_main.cpp test_sdl_geo.cpp $(LIBS)


test_performance:
	$(CC) $(CFLAGS) -o test_performance speed_test.cpp $(LIBS)




clean:
	rm -rf test_performance
