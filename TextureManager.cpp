#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.hpp"
#include "DebugRender.hpp"

TextureManager* TextureManager::s_pInstance = 0;
#include "Game.hpp"

#include "assets/XPMLoader.hpp"
#include "assets/Particles.xpm"
#include "assets/HexCellBorder.xpm"
#include "assets/Glyph.xpm"


bool TextureManager::init()
{
	load(XPMLoadFromStaticCharArray(Glyph_xpm),"glyph",TheGame::Instance()->getRenderer());
	load(XPMLoadFromStaticCharArray(Particles_xpm),"greyscale", TheGame::Instance()->getRenderer());
	load(XPMLoadFromStaticCharArray(HexCell_xpm),"hexcell",TheGame::Instance()->getRenderer());

	return true;
}


bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if(pTempSurface == 0)
		return false;

	SDL_Texture* pTexture = 
	SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	print_texture_info(fileName,pTexture);

	if(pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

SDL_Texture* TextureManager::load(char **xpm, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_ReadXPMFromArray(xpm);
	if(pTempSurface == 0)
		return NULL;

	Uint32 t_pixel = SDL_MapRGB(pTempSurface->format,0xff,0xff,0xff);

	if(SDL_SetColorKey(pTempSurface,SDL_TRUE,t_pixel) < 0)
	{
		cout << "Couldn't set alpha pixel: " << SDL_GetError() << endl;
		SDL_FreeSurface(pTempSurface);
		return NULL;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);
	return pTexture;
}


bool TextureManager::load(char **xpm, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Texture* pTexture = load(xpm,pRenderer);

	if(pTexture != 0)
	{
		print_texture_info(id,pTexture);

		if(m_textureMap.find(id) != m_textureMap.end())
			SDL_DestroyTexture(m_textureMap[id]);
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

bool TextureManager::clean()
{
	for(auto tp : m_textureMap)
	{
		SDL_DestroyTexture(tp.second);
	}
	return true;
}

void TextureManager::draw(SDL_Texture *pTexture, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, pTexture, &srcRect,
	&destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	draw(m_textureMap[id],x,y,width,height,pRenderer,flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	
	destRect.w = 1*(srcRect.w = width);
	destRect.h = 1*(srcRect.h = height);

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
