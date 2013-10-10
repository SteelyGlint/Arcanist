
#include "Game.hpp"
#include "SDLGameObject.hpp"
#include "TextureManager.hpp"




SDLGameObject::SDLGameObject(LoaderParams const& pParams) 
	: GameObject(pParams),
	   m_x(pParams.x()), m_y(pParams.y()), m_width(pParams.width()),
	   m_height(pParams.height()), m_textureID(pParams.textureID()),
	   m_currentFrame(1), m_currentRow(1), m_startTick(SDL_GetTicks())
{ }

void SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}


