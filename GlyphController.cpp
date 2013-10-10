#include<iostream>
#include <algorithm>

#include <SDL.h>
#include "GlyphController.hpp"

#include "Game.hpp"
#include "TextureManager.hpp"
#include "assets/Glyph.xpm"

GlyphController* GlyphController::s_pInstance = NULL;

bool GlyphController::init()
{
	return TextureManager::Instance()->load(Glyph_xpm,"glyph",TheGame::Instance()->getRenderer());
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
	for( auto const & g : m_mapGlyph )
	{
		const int W = TheHexGrid::Instance()->get_hex_width();
		const double R = W/2.000;


		const int S = (3.00*R)/2.00;
		const int H = (sqrt(3)*R);


		const int width = 22;	
		const int height = 22;

		int x, y;
		std::tie(x,y) = g.first;


		TextureManager::Instance()->draw(
			"glyph",
			x*S /*center hex */ + width/2,
			y*H + (x%2)*(H/2.00) /*center hex */ + height/2,
			width,height,TheGame::Instance()->getRenderer());
	}
}

bool GlyphController::placeGlyph(HexIndex loc, Glyph_Type g_type)
{
	bool ret;
	std::tie(std::ignore,ret) = m_mapGlyph.insert( std::make_pair(loc, Glyph::GlyphGraphicalObject(LoaderParams{0,0,22,22,"glyph"})));
	return ret;
}



bool GlyphController::debugGlyphs()
{
	int i = 0;
	for( auto & g : m_mapGlyph )
	{
		std::cout << g.second.data().m_loc.first << 'x' << g.second.data().m_loc.second << '\n';
		++i;
	}

	std::cout << "Found " << i << "Glyphs.\n";
}
