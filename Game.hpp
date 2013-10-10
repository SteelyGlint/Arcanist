#ifndef __Game_hpp__
#define __Game_hpp__
#include <vector>
#include <string>
#include "SDL.h"
#include "HexGrid.hpp"
#include "MoteMovementManager.hpp"


class Game
{
public:

	bool init(const std::string &title, int x, int y, int width, int height, Uint32 flags);

	void draw();
	void render();
	void update();
	void handleEvents();

	bool running() const { return m_bRunning; }
	void clean();

	void quit();


	SDL_Renderer* getRenderer() const { return rend; }

	static Game* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}


private:
	SDL_Window* win;
	SDL_Renderer* rend;
	
	int m_currentFrame = 0;
	bool m_bRunning = true;

	Game() = default;
	~Game() = default;
	static Game* s_pInstance;

};

typedef Game TheGame;


#endif
