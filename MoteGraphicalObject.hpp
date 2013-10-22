#ifndef __MoteGraphicalObject_hpp__
#define __MoteGraphicalObject_hpp__

#include <string>
#include <cstdint>
#include "SDLGameObject.hpp"


namespace Wand
{

constexpr uint8_t North = 0x01;
constexpr uint8_t East = 0x02;
constexpr uint8_t West = 0x04;
constexpr uint8_t South = 0x08;

enum class Bearing : std::uint8_t 
	{ 
		NW = North | West,
		N  = North, 
		NE = North | West, 

		E = East, 

		SE = South | East, 
		S  = South, 
		SW = South | West, 

		W = West,
	};


class MoteGraphicalObject : public SDLGameObject
{
public:
	MoteGraphicalObject(LoaderParams const &pParams)
		: SDLGameObject(pParams) { }

	virtual void draw();
	virtual void update();
	//virtual void clean();

	void setBearing(Bearing b) { m_bearing = b; }

	int x() { return SDLGameObject::m_x; }
	int y() { return SDLGameObject::m_y; }

protected:
	Bearing m_bearing;
};

};

#endif
