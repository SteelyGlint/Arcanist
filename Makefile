CC=clang++
INCLUDES=-I/usr/include/SDL2 -I. -Iutil/ -I/usr/local/
CFLAGS=-O0 -c -g $(INCLUDES) -std=c++11 -Wall #-pedantic -Werror
LDFLAGS=`sdl2-config --libs` -lSDL2_image


SOURCES=main.cpp Game.cpp GlyphGraphicalObject.cpp HexCell.cpp InputHandler.cpp MoteGraphicalObject.cpp SDLGameObject.cpp TextureManager.cpp GlyphController.cpp GraphicalHexGrid.cpp MoteMovementManager.cpp SignalManager.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=helloworld

all:$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf helloworld *.o
