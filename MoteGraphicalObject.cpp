#include <SDL.h>
#include "MoteGraphicalObject.hpp"


void MoteGraphicalObject::draw()
{
	SDLGameObject::draw();
}


void MoteGraphicalObject::update()
{
	//todo:
		//parameterize refreshrate: 100
		//encapsulate number of frames within xpm pixmap
	m_currentFrame = int(((SDL_GetTicks()/ 100) % 6));

	if(static_cast<std::uint8_t>(m_bearing) & North)
		m_y += 1;

	if(static_cast<std::uint8_t>(m_bearing) & South)
		m_y -= 1;

	if(static_cast<std::uint8_t>(m_bearing) & East)
		m_x += 1;

	if(static_cast<std::uint8_t>(m_bearing) & West)
		m_x -= 1;
}
