#include <iostream>
#include <SDL.h>

#include "SignalManager.hpp"
#include "HexGrid.hpp"
#include "MoteGraphicalObject.hpp"

#include "Glyph.hpp"
#include "GlyphController.hpp"

SignalManager * SignalManager::p_sInstance = NULL;

using namespace Glyph;

bool SignalManager::init()
{
}

void SignalManager::update()
{
	//m_currentGameTick
	//send_count
	//while m_currentGameTick < m_gameMessages.front().next_tick()
		//pop
		//Create SignalDirected
		//generate SDL_event
		//if ++send_count >= max_signal_per_tick
			//break;
}

void SignalManager::draw()
{
}


void SignalManager::clean()
{
}


