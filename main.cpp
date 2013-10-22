/* vi: set ts=4 sw=4 expandtab: */
#include <cassert>
#include <iostream>
#include <string>
using std::string;

#include <SDL.h>

#include "Game.hpp"
#include "InputHandler.hpp"
#include "GlyphController.hpp"

static bool no_updates = false;
static int delay = 5;

using namespace Wand;

void pause_func(SDL_Scancode key, bool pressed)
{
	if( pressed )
	{
		std::cout << "paused\n";
		no_updates = true;
	} else {
		std::cout << "unpaused\n";
		no_updates = false;
	}
}

void playback_func(SDL_Scancode key, bool pressed)
{
	if( pressed )
	{
		if(key == SDL_SCANCODE_PAGEUP)
			delay = (delay + 50 > 500) ? 500 : delay + 50;
		if(key == SDL_SCANCODE_PAGEDOWN)
			delay = (delay - 50 < 5) ? 5 : delay - 50;
	}
}

int main()
{
	const string win_title{"Particle Test"};

	assert(TheGame::Instance()->init("Particle Test",50,50,640,480,SDL_WINDOW_SHOWN));
		
   TheInputHandler::Instance()->addKeyChangedFunc(SDL_SCANCODE_SPACE,&pause_func);
   TheInputHandler::Instance()->addKeyChangedFunc(SDL_SCANCODE_PAGEUP,&playback_func);
   TheInputHandler::Instance()->addKeyChangedFunc(SDL_SCANCODE_PAGEDOWN,&playback_func);

	while(Game::Instance()->running())
	{
		Game::Instance()->handleEvents();
		if(!no_updates)
			Game::Instance()->update();
		Game::Instance()->render();
		SDL_Delay(delay);
	}

	Game::Instance()->clean();

	return 0;
}
