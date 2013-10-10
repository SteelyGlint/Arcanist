#ifndef __InputHandler_hpp__
#define __InputHandler_hpp__
#include <vector>
#include <utility>
#include <cassert>
#include <SDL.h>

#include "impl/ImplInputHandler.hpp"
#include "impl/ImplKeyInputHandler.hpp"


namespace Handler {

class MouseInputHandler : public MouseInput
{
public:
	void update(SDL_Event const& event);
	bool getMouseButtonState(int buttonNumber) const
	{
		return m_mouseButtonStates[buttonNumber];
	}

	std::pair<int,int> const & getMousePosition() const { return m_mousePosition; }

private:
	std::pair<int,int> m_mousePosition{0,0};
};


class KeyInputHandler : public KeyInput
{
public:
	bool init()
	{
		return KeyInput::init();
	}

	void update()
	{
		KeyInput::update();
	}


	bool isKeyDown(SDL_Scancode key)
	{
		return KeyInput::isKeyDown(key);
	}

	void onKeyUp(SDL_Scancode key)
	{
		KeyInput::onKeyUp(key);
	}

	void onKeyDown(SDL_Scancode key)
	{
		KeyInput::onKeyDown(key);
	}

	void clean()
	{
		KeyInput::clean();
	}
};


class InputHandler 
{
public:
	static InputHandler* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}

	void update();
	void clean();


	bool getMouseButtonState(int buttonNumber) const
	{
		return m_mouseHandler.getMouseButtonState(buttonNumber);
	}

	std::pair<int,int> const & getMousePosition() const 
	{ 
		return m_mouseHandler.getMousePosition();
	}

	template<int BUTTON, int DEPRESSED_STATE>
	std::pair<int,int> const & getMousePosition() const 
	{
		return m_mouseHandler.MouseInput::getMousePosition<BUTTON,DEPRESSED_STATE>();
	}


	template<typename FUNC>
	void addKeyChangedFunc(SDL_Scancode key, FUNC f)
	{
		m_keyHandler.addKeyChangedFunc(key,f);
	}


	void remKeyChanged(SDL_Scancode key)
	{
		m_keyHandler.remKeyChanged(key);
	}
	


	bool init();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }

private:
	void initialiseJoysticks();

	std::vector<SDL_Joystick *> m_joysticks;
	bool m_bJoysticksInitialised = false;

	MouseInputHandler m_mouseHandler;
	KeyInputHandler m_keyHandler;


	InputHandler() = default;
	~InputHandler() = default;
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;
}; /* namespace handler */
#endif
