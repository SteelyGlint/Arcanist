#ifndef __HexCell_hpp__
#define __HexCell_hpp__
#include <utility>
#include <cstddef>

namespace Wand
{
	using HexIndex = std::pair<uint8_t,uint8_t>;

	enum HexDirection : uint8_t { NORTHWEST, NORTH, NORTHEAST, SOUTHEAST, SOUTH, SOUTHWEST };

	struct HexCell
	{
		HexIndex index;
	};

};

#endif
