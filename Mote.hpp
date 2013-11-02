#ifndef __Mote_hpp__
#define __Mote_hpp__
#include <cstdint>
#include <utility>
#include <array>
#include <bitset>
#include <string>

#include "util/HexDim.hpp"

namespace Wand 
{
constexpr std::size_t NUM_COMPONENTS_PER_MOTE = 4;
constexpr std::size_t NUM_ELEMENTS = 6;

enum class Element : uint8_t { Void, Chaos, Fire, Spark, Life, Flow };

struct Component
{
	Element element;
	uint8_t quality;

	uint32_t weight() { return 1; }

	operator Element() const { return element; }
};

struct Mote
{
	std::size_t size = 0;
	std::array<Component,NUM_COMPONENTS_PER_MOTE> components;
	std::bitset<NUM_ELEMENTS> elements;

	typedef wand::hex::detail::hex_point_type point_type;
	wand::hex::detail::hex_point_type position;

	template<typename Comp>
	bool add(Comp&& c);

	uint32_t weight();

};

template<typename Comp>
bool Mote::add(Comp&& c)
{
	if(size == NUM_COMPONENTS_PER_MOTE)
		return false;

	components[size++] = std::forward<Comp>(c);
	elements[static_cast<uint8_t>((Element)c)] = true;
	return true;
}

uint32_t Mote::weight()
{
	uint32_t ret = 0;
	for(std::size_t i = 0; i < size;++i)
		ret += components[i].weight();
	return ret;
}




};

#endif
