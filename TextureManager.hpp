#ifndef __TextureManager_hpp__
#define __TextureManager_hpp__
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	SDL_Texture* load(char **xpm, SDL_Renderer* pRenderer);

	bool load(char **xpm, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw(SDL_Texture *pTexture, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);


	static TextureManager* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool clean();
protected:
	std::map<std::string, SDL_Texture*> m_textureMap;
	static TextureManager* s_pInstance;

private:
	TextureManager() { }
};
#endif
