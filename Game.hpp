#ifndef __Game_hpp__
#define __Game_hpp__
#include <vector>
#include <string>
#include <SDL.h>
//#include "HexCell.hpp"
//#include "MoteMovementManager.hpp"


namespace Wand
{
class Game
{
public:

	bool init(const std::string &title, int x= SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int width = 640, int height = 480, Uint32 flags = SDL_WINDOW_SHOWN );

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
	
	bool m_bRunning;
	static Game* s_pInstance;

	Game() : win(NULL), rend(NULL), m_bRunning(true) {}

};
typedef Game TheGame;
};


#endif
