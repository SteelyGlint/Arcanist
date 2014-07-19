/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It was built successfully with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0  -o%TEMP%\metaprogram-chapter9-example1.exe example1.cpp
        
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



*/
#include <iostream>
#include <typeinfo>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

SDL_EventType AllEventTypes[] = 
{ SDL_WINDOWEVENT,SDL_SYSWMEVENT,SDL_KEYDOWN,SDL_KEYUP,SDL_TEXTEDITING,SDL_TEXTINPUT,SDL_MOUSEMOTION,SDL_MOUSEBUTTONDOWN,SDL_MOUSEBUTTONUP,SDL_MOUSEWHEEL,SDL_INPUTMOTION,SDL_INPUTBUTTONDOWN,SDL_INPUTBUTTONUP,SDL_INPUTWHEEL,SDL_INPUTPROXIMITYIN,SDL_INPUTPROXIMITYOUT,SDL_JOYAXISMOTION,SDL_JOYBALLMOTION,SDL_JOYHATMOTION,SDL_JOYBUTTONDOWN,SDL_JOYBUTTONUP,SDL_JOYDEVICEADDED,SDL_JOYDEVICEREMOVED,SDL_CONTROLLERAXISMOTION,SDL_CONTROLLERBUTTONDOWN,SDL_CONTROLLERBUTTONUP,SDL_CONTROLLERDEVICEADDED,SDL_CONTROLLERDEVICEREMOVED,SDL_FINGERDOWN,SDL_FINGERUP,SDL_FINGERMOTION,SDL_TOUCHBUTTONDOWN,SDL_TOUCHBUTTONUP,SDL_DOLLARGESTURE,SDL_DOLLARRECORD,SDL_MULTIGESTURE,SDL_CLIPBOARDUPDATE,SDL_DROPFILE
};

void test_eventtypes()
{
	SDL_EventType event;
	for(int i = 0; i < sizeof(AllEventTypes) / sizeof(SDL_EventType);++i)
	{
		event = AllEventType[i];
		std::cout << "Event " <<( SDL_GetEventState(event) ? "Enabled" : "Ignored" ) << std::endl;
	}
}

int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 0;
	test_eventtypes();
}
