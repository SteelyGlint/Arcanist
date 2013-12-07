#include <utility>
#include <cstddef>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "assets/XPMLoader.hpp"
#include <assets/HexCellBorder.xpm>
#include "HexCell.hpp"

namespace Wand
{

HexCell::HexCell(SDL_Renderer *rend)
	: m_rend(rend), m_texture(nullptr)
{
	SDL_Surface* pTempSurface = IMG_ReadXPMFromArray(XPMLoadFromStaticCharArray(HexCell_xpm));

	if(!pTempSurface)
	{
		std::cout << "Couldn't load XPM: " << SDL_GetError() << std::endl;
		return;
	}

	Uint32 t_pixel = SDL_MapRGB(pTempSurface->format,0xff,0xff,0xff);

	if(SDL_SetColorKey(pTempSurface,SDL_TRUE,t_pixel) < 0)
	{
		std::cout << "Couldn't set alpha pixel: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(pTempSurface);
		return;
	}

	m_texture = SDL_CreateTextureFromSurface(rend, pTempSurface);
	SDL_FreeSurface(pTempSurface);

}


void HexCell::draw(SDL_Rect const &dest) const
{
	SDL_RenderCopy(m_rend,m_texture,NULL,&dest);
}

}


