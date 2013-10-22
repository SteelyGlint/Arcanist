#include <iostream>
#include <SDL.h>

#include "SignalManager.hpp"
#include "HexCell.hpp"
#include "MoteGraphicalObject.hpp"

#include "Glyph.hpp"
#include "GlyphController.hpp"

namespace Wand
{
SignalManager * SignalManager::p_sInstance = NULL;

bool SignalManager::init()
{
	return true;
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


};
