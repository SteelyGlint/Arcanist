/* vi: set ts=4 sw=4 expandtab: */
#include <SDL.h>
#include "Game.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "GraphicalHexGrid.hpp"
#include "util/DebugRender.hpp"


#include "MoteGraphicalObject.hpp"

#include "MoteMovementManager.hpp"
#include "GlyphController.hpp"

namespace Wand {

Game * Game::s_pInstance = nullptr;


#define SUBSYS(arg) if(!arg::Instance()->init()) \
                    {\
                        std::cerr << "Subsystem " << #arg << " failed to init.\n";\
                        return false;\
                    }


bool Game::init(const std::string &title, int x, int y, int width, int height, Uint32 flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;


	win = SDL_CreateWindow("Arcanist", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, flags);

	if( win == 0 )
		return false;

	rend = SDL_CreateRenderer(win, -1, 0);

	if(rend == 0)
		return false;

	print_render_info(rend);
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

	int win_w, win_h;
	SDL_GetWindowSize(win,&win_w,&win_h);

	SUBSYS(TheTextureManager)
	SUBSYS(TheInputHandler)
	SUBSYS(TheGlyphController)
	SUBSYS(TheMoteMovementManager)

	if(!TheHexGrid::Instance()->init(win_w,win_h,11,11,rend))
	{
		std::cerr << "Subsystem HexGrid failed to init.\n";
		return false;
	}

	return true;
}

void Game::draw()
{
	TheHexGrid::Instance()->draw();
	TheGlyphController::Instance()->draw();
	TheMoteMovementManager::Instance()->draw();
}

void Game::render()
{
	SDL_RenderClear(rend);
	draw();
	SDL_RenderPresent(rend);
}

void Game::update()
{
	TheMoteMovementManager::Instance()->update();
	TheGlyphController::Instance()->update();


/*
	static bool prior_state = TheInputHandler::Instance()->getMouseButtonState(LEFT);
	if(prior_state != TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		const std::pair<int,int> m_pos_1 = TheInputHandler::Instance()->getMousePosition<LEFT,0x001>();
		const std::pair<int,int> m_pos_2 = TheInputHandler::Instance()->getMousePosition<LEFT,0x002>();

		HexIndex h_id[2] = {
			TheHexGrid::Instance()->atPoint(m_pos_1.first,m_pos_1.second),
			TheHexGrid::Instance()->atPoint(m_pos_2.first,m_pos_2.second)
		};

		std::cerr << "Mouse pos1 " << m_pos_1.first << 'x' << m_pos_1.second << " is in hex " << h_id[0].first << 'x' << h_id[0].second << std::endl;
		std::cerr << "Mouse pos2 " << m_pos_2.first << 'x' << m_pos_2.second << " is in hex " << h_id[1].first << 'x' << h_id[1].second << std::endl;

		prior_state = TheInputHandler::Instance()->getMouseButtonState(LEFT);

	//	std::cerr << "add glyph " <<
	//	TheGlyphController::Instance()->placeGlyph(h_id[0]) << std::endl;


	}
*/

	
}

void Game::quit()
{
	std::cerr << "Game::quit()\n";
	m_bRunning = false;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

void Game::clean()
{
	TheMoteMovementManager::Instance()->clean();
	TheGlyphController::Instance()->clean();
	TheInputHandler::Instance()->clean();
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

} /* namespace Wand */
