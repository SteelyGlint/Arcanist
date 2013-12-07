#include <iostream>

#include <SDL.h>

#include <util/SDL_BoostGeomPoint.hpp>
#include "TextureManager.hpp"
#include "Game.hpp"
#include "GraphicalHexGrid.hpp"

namespace Wand {

HexGrid* HexGrid::s_pInstance = 0;

bool HexGrid::init(int w, int h,int rows, int cols)
{
	std::cerr << "Grid Dimensions: " << w << 'x' << h << std::endl;
	m_dim = std::make_pair(w,h);

	m_pHexGrid = std::unique_ptr<hexgrid_type>(new hexgrid_type(rows,cols));
	
	win_w = w;
	win_h = h;

	return true;
}


HexIndex HexGrid::atPoint(int x, int y)
{
	const int W = hex_width;
	const float R = W/2.000;
	const int S = (3.00*R)/2.00;
	const int H = (sqrt(3)*R);

	int i_t = floor(x/S);

	int y_ts = (float)y - (i_t%2)*(H/2);
	int j_t = floor(y_ts/H);


	int x_t = x - i_t * S;
	int y_t = y_ts - j_t*H;

	int i = (x_t > R*abs(0.500 - y_t/H)) ? i_t : i_t - 1;
	int j = (x_t > R*abs(0.500 - y_t/H)) ? j_t : j_t - i%2 + ((y_t > H/2) ? 1 : 0);

	return HexIndex(i,j);
}

void HexGrid::draw()
{
	SDL_Renderer * const rend(Game::Instance()->getRenderer());
	static HexCell tCell(rend);

	auto to_pixel = m_pHexGrid->hexRingToPixelMapper(win_w,win_h);

	auto render_func = [&tCell,rend](const pixel_ring_type &pixel_ring){ 
		SDL_BBox destCell;
		boost::geometry::envelope(pixel_ring,destCell);
		SDL_Rect destRect((SDL_Rect)destCell);
		tCell.draw(destRect);
	};

	to_pixel(render_func);
}




} /*namespace Wand */
