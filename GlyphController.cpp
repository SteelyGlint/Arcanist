#include<iostream>
#include <algorithm>

#include <SDL.h>
#include "GlyphController.hpp"

#include "Game.hpp"
#include "TextureManager.hpp"

namespace Wand {

GlyphController* GlyphController::s_pInstance = NULL;

bool GlyphController::init()
{
	return true;
}

void GlyphController::clean()
{
	m_mapGlyph.clear();
}
	
void GlyphController::update()
{
	for( auto & g : m_mapGlyph )
	{
		g.second.update();
	}
}

void GlyphController::draw()
{
	for( auto & g : m_mapGlyph )
	{
		g.second.draw();
	}
}


} /* namespace Wand */
