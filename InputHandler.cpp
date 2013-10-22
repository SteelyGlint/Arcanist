#include <iostream>
#include <SDL.h>
#include "InputHandler.hpp"
#include "Game.hpp"

namespace Wand {
InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::update()
{
	m_keyHandler.update();

	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type & 0xff00)
		{
			case 0x100:
				if(event.type == SDL_QUIT)
					TheGame::Instance()->quit();
				break;
			case 0x400:
				m_mouseHandler.update(event);
				break;
			case 0x300:
				if(event.type == SDL_KEYDOWN)
				{
					m_keyHandler.onKeyDown(event.key.keysym.scancode);
					break;
				}

				if(event.type == SDL_KEYUP)
				{
					m_keyHandler.onKeyUp(event.key.keysym.scancode);
					break;
				}

				break;
			default:
				break;
		}
	}
}

void InputHandler::clean()
{
	//m_mouseHandler.clean();
	m_keyHandler.clean();
	if(m_bJoysticksInitialised)
	{
		for(int i = 0; i < SDL_NumJoysticks();++i)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

bool InputHandler::init()
{
	//m_mouseHandler.init();
	m_keyHandler.init();
	initialiseJoysticks();
	return true;
}

void InputHandler::initialiseJoysticks()
{
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if(SDL_NumJoysticks() > 0)
	{
		for(int i = 0; i < SDL_NumJoysticks();++i)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if(joy)
			{
				m_joysticks.push_back(joy);
			} else {
				std::cerr << "JoyStick init: " << SDL_GetError();
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << " joystick(s)" << std::endl;
	} else {
		m_bJoysticksInitialised = false;
	}
}

void MouseInputHandler::update(SDL_Event const &event)
{
	if(event.type & 0x0003) 
		/* SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONDOWN */
	{
		int x,y;
		Uint32 b_mask = SDL_GetMouseState(&x,&y);

		mouse_update_buttons_state<LEFT>(b_mask,event);
		mouse_update_buttons_state<MIDDLE>(b_mask,event);
		mouse_update_buttons_state<RIGHT>(b_mask,event);

		m_mousePosition = std::pair<int,int>(x,y);
	}  else if(event.type == SDL_MOUSEMOTION) {
		m_mousePosition = std::make_pair(event.motion.x,event.motion.y);
	}



}



}; /* namespace Handler */

