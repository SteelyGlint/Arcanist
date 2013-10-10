#ifndef __ImplKeyInputHandler_hpp__
#define __ImplKeyInputHandler_hpp__
#include <SDL.h>
#include <utility>
#include <set>
#include <map>
#include <functional>

namespace Handler {

class KeyInput
{
public:
	Uint8* m_keystate   = 0;
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


#endif
