#ifndef __InputHandler_hpp__
#define __InputHandler_hpp__
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cassert>
#include <functional>

#include <SDL.h>

namespace Wand
{
	enum mouse_buttons
	{
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
	};

	template<int BUTTON>
	struct button_mask
	{
		const static int value = 0;
	};

	template<>
	struct button_mask<RIGHT>
	{
		const static int value = SDL_BUTTON_RMASK;
	};

	template<>
	struct button_mask<MIDDLE>
	{
		const static int value = SDL_BUTTON_MMASK;
	};

	template<>
	struct button_mask<LEFT>
	{
		const static int value = SDL_BUTTON_LMASK;
	};



	class MouseInput
	{
		public:
		std::vector<bool> m_mouseButtonStates{false,false,false};

		std::vector<std::pair<int,int> > m_mouseButtonPos
		{/* Button Down */
			std::pair<int,int>{-1,-1}, /* LEFT */
			std::pair<int,int>{-1,-1}, /* MIDDLE */
			std::pair<int,int>{-1,-1},  /* RIGHT */
			/* Button Up */
			std::pair<int,int>{-1,-1}, /* LEFT */
			std::pair<int,int>{-1,-1}, /* MIDDLE */
			std::pair<int,int>{-1,-1},  /* RIGHT */

		};

		template<int BUTTON, int DEPRESSED_STATE>
		std::pair<int,int> const & getMousePosition() const 
		{ 
			int offset = (DEPRESSED_STATE & 0xFF01) ? 0 : (DEPRESSED_STATE & 0xFF02) ? 3 : -1;

			assert(offset >= 0);
			offset += BUTTON;
			return m_mouseButtonPos[offset];
		}

		template<int BUTTON> /* mouse event position helper func */
		void update_pos(SDL_Event const& event, bool btn_state)
		{
			if(m_mouseButtonStates[BUTTON] != btn_state)
			{
				m_mouseButtonPos[(btn_state ? 0 : 3) + BUTTON] = std::pair<int,int>(event.button.x,event.button.y);
				m_mouseButtonStates[BUTTON] = btn_state;
			}

		}

		template<int BUTTON>
		void mouse_update_buttons_state(Uint32 &b_mask,SDL_Event const &event)
		{
			const bool btn_state = m_mouseButtonStates[BUTTON];
			const bool eval_state = (bool)(b_mask & button_mask<BUTTON>::value);
			if(btn_state != eval_state)
			{
				update_pos<BUTTON>(event,!btn_state);
				m_mouseButtonStates[BUTTON] = eval_state;
			}
		
		}


	
	};



};


namespace Wand {

class KeyInput
{
public:
	const Uint8* m_keystate;
	Uint8* m_keyhistory = 0;
	int num_keys;

	std::multimap<SDL_Scancode,
		std::function<void(SDL_Scancode,bool)> > m_mapkey_changed;

	std::set<SDL_Scancode> m_setkey_cache;

	bool init()
	{
		m_keystate = SDL_GetKeyboardState(&num_keys);
		m_keyhistory = new Uint8[num_keys];
		for(int i = 0; i < num_keys;++i)
			m_keyhistory[i] = m_keystate[i];
		return true;
	}

	void clean()
	{
		if( m_keyhistory != 0 )
			delete [] m_keyhistory;

		m_mapkey_changed.clear();	
		m_setkey_cache.clear();
	}

	void update()
	{

//SDL_PumpEvents //force event queue update
	/*  implicitatly called from SDL_PollEvent and SDL_WaitEvent */

		m_keystate = SDL_GetKeyboardState(NULL);
	}

	bool isKeyDown(SDL_Scancode key)
	{
		if(m_keystate == 0)
			return false;
	
		return m_keystate[key];
	}


	template<typename T>
	void key_changed_handler_forwarder(std::pair<T,T> p_tt,bool key_down)
	{
		key_changed_handler_forwarder(p_tt.first,p_tt.second,key_down);
	}

	template<typename Iter>
	void key_changed_handler_forwarder(Iter it_start, Iter it_end,bool key_down)
	{
		for(;it_start != it_end;++it_start)
		{
			it_start->second(it_start->first,key_down);
		}
	}

	void onKeyDown(SDL_Scancode key)
	{
		if(m_setkey_cache.find(key) != m_setkey_cache.end())
		{
			if(isKeyDown(key) && !m_keyhistory[key])
			{
				m_keyhistory[key] = true;
				key_changed_handler_forwarder(m_mapkey_changed.equal_range(key),true);
			}
		}
	}

	void onKeyUp(SDL_Scancode key)
	{
		if(m_setkey_cache.find(key) != m_setkey_cache.end())
		{
			if(!isKeyDown(key) && m_keyhistory[key])
			{
				m_keyhistory[key] = false;
				key_changed_handler_forwarder(m_mapkey_changed.equal_range(key),false);
			}
		}
	}

	
	void addKeyChangedFunc(SDL_Scancode key, std::function<void(SDL_Scancode,bool)> f)
	{
		m_mapkey_changed.insert( std::make_pair(key,f) );
		m_setkey_cache.insert(key);
	}

	void remKeyChanged(SDL_Scancode key)
	{
		m_mapkey_changed.erase(key);
		m_setkey_cache.erase(key);
	}

};

}; 


namespace Wand
{

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

}; /*namespace Wand */

typedef Wand::InputHandler TheInputHandler;
#endif
