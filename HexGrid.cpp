#include <iostream>

#include "SDL.h"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "HexGrid.hpp"

HexGrid* HexGrid::s_pInstance = 0;

bool HexGrid::init(int w, int h)
{
	hex_width = 54;
	hex_height = 45;

	std::cerr << "Grid Dimensions: " << w << 'x' << h << std::endl;
//	std::cerr << "Grid Texture: " << h_width << 'x' << h_height << std::endl;

	m_dim = std::make_pair(w,h);

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
	const int W = hex_width;
	const double R = W/2.000;

	const int S = (3.00*R)/2.00;
	const int H = (sqrt(3)*R);

	for(int i = 0;i < m_dim.first;++i)
	{
		for(int j = 0;j < m_dim.second;++j)
		{
			TextureManager::Instance()->draw("hexcell",i*S,j*H + (i%2)*(H/2.00),W,H,Game::Instance()->getRenderer());
		}
	}

}
