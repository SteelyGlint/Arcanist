#ifndef __Mote_hpp__
#define __Mote_hpp__
#include <cstddef>
#include <utility>

#include <HexCell.hpp>
#include <util/Vector.hpp>

namespace Wand 
{
static const int NUM_COMPONENTS_PER_MOTE = 4;
enum class Element : uint8_t { Void, Chaos, Fire, Spark, Life, Flow };

struct Component
{
	uint8_t element = 0;
	uint8_t quality = 0;
	uint32_t weight() { return 1; }
};

struct Mote
{
	Component components[NUM_COMPONENTS_PER_MOTE] = {{0,0},{0,0},{0,0},{0,0}};
	uint size = 0;

	uint32 weight()
	{
		uint32_t ret = 0;
		for(int i = 0; i < size;++i)
			ret += components[i].weight();
		return ret;
	}

	Vector2D<float,float> position;
	HexDirection bearing;

	HexCell* hex_position = nullptr;
};

};

#endif
