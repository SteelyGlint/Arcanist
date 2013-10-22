/* vi: set ts=4 sw=4 expandtab: */
#include <SDL.h>
#include "Game.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "DebugRender.hpp"


#include "MoteGraphicalObject.hpp"

#include "GlyphController.hpp"

namespace Wand {

Game * Game::s_pInstance = nullptr;


bool Game::init(const std::string &title, int x, int y, int width, int height, Uint32 flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	win = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);

	if( win == 0 )
		return false;

	rend = SDL_CreateRenderer(win, -1, 0);

	if(rend == 0)
		return false;

	print_render_info(rend);
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

	if(!TheTextureManager::Instance()->init())
	{
		return false;
	}

	if(!TheGlyphController::Instance()->init())
	{
		return false;
	}

	if(!TheMoteMovementManager::Instance()->init())
	{
		return false;
	}

	TheInputHandler::Instance()->init();

	return true;
}

void Game::draw()
{
	//TheHexGrid::Instance()->draw();

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

	static bool prior_state = TheInputHandler::Instance()->getMouseButtonState(LEFT);
	if(prior_state != TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		const std::pair<int,int> m_pos_1 = TheInputHandler::Instance()->getMousePosition<LEFT,0x001>();
		const std::pair<int,int> m_pos_2 = TheInputHandler::Instance()->getMousePosition<LEFT,0x002>();

/*
		HexIndex h_id[2] = {
			TheHexGrid::Instance()->atPoint(m_pos_1.first,m_pos_1.second),
			TheHexGrid::Instance()->atPoint(m_pos_2.first,m_pos_2.second)
		};

		std::cerr << "Mouse pos1 " << m_pos_1.first << 'x' << m_pos_1.second << " is in hex " << h_id[0].first << 'x' << h_id[0].second << std::endl;
		std::cerr << "Mouse pos2 " << m_pos_2.first << 'x' << m_pos_2.second << " is in hex " << h_id[1].first << 'x' << h_id[1].second << std::endl;

		prior_state = TheInputHandler::Instance()->getMouseButtonState(LEFT);

	//	std::cerr << "add glyph " <<
	//	TheGlyphController::Instance()->placeGlyph(h_id[0]) << std::endl;
*/

	}

	
}

void Game::quit()
{
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
