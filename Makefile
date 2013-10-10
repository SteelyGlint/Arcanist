CC=g++
INCLUDES=-I/usr/include/SDL2
CFLAGS=-O0 -g $(INCLUDES) -std=c++11 -Wall #-pedantic -Werror
LIBS=-lSDL2 -lSDL2_image


.PHONY: depend clean


helloworld:main.cpp Game.o TextureManager.o SDLGameObject.o SignalManager.o GlyphController.o MoteMovementManager.o GlyphGraphicalObject.o MoteGraphicalObject.o HexGrid.o InputHandler.o
	$(CC) $(CFLAGS) -o helloworld main.cpp Game.o TextureManager.o InputHandler.o SignalManager.o GlyphController.o GlyphGraphicalObject.o MoteMovementManager.o SDLGameObject.o MoteGraphicalObject.o HexGrid.o $(LIBS) 

MoteMovementManager.o:MoteMovementManager.hpp Glyph.hpp HexGrid.hpp HexGrid.o GlyphController.hpp GlyphController.o MoteMovementManager.cpp
	$(CC) $(CFLAGS) -c MoteMovementManager.cpp $(LIBS)

SignalManager.o:SignalManager.hpp Glyph.hpp GlyphController.hpp GlyphController.o SignalManager.cpp
	$(CC) $(CFLAGS) -c SignalManager.cpp $(LIBS)

SDLGameObject.o:GameObject.hpp SDLGameObject.hpp SDLGameObject.cpp
	$(CC) $(CFLAGS) -c SDLGameObject.cpp $(LIBS)

MoteGraphicalObject.o:GameObject.hpp SDLGameObject.o MoteGraphicalObject.hpp MoteGraphicalObject.cpp
	$(CC) $(CFLAGS) -c MoteGraphicalObject.cpp $(LIBS)

GlyphController.o:Glyph.hpp GlyphController.hpp GlyphController.cpp
	$(CC) $(CFLAGS) -c GlyphController.cpp $(LIBS)

GlyphGraphicalObject.o:GameObject.hpp SDLGameObject.o Glyph.hpp GlyphController.hpp GlyphGraphicalObject.cpp
	$(CC) $(CFLAGS) -c GlyphGraphicalObject.cpp $(LIBS)

HexGrid.o:HexGrid.hpp HexGrid.cpp assets/HexCell.xpm assets/HexCellBorder.xpm
	$(CC) $(CFLAGS) -c HexGrid.cpp $(LIBS)

TextureManager.o:TextureManager.cpp TextureManager.hpp
	$(CC) $(CFLAGS) -c TextureManager.cpp $(LIBS)

InputHandler.o:InputHandler.hpp InputHandler.cpp
	$(CC) $(CFLAGS) -c InputHandler.cpp $(LIBS)

Game.o:Game.hpp Game.cpp assets/Particles.xpm
	$(CC) $(CFLAGS) -c Game.cpp $(LIBS)


clean:
	rm -rf helloworld Game.o MoteGraphicalObject.o SDLGameObject.o GameObject.o TextureManager.o InputHandler.o HexGrid.o GlyphController.o GlyphGraphicalObject.o SignalManager.o MoteMovementManager.o
test:
	g++ -O2 -g -I/usr/include/SDL2 -std=c++11 -o a.out test_palette.cpp -lSDL2
