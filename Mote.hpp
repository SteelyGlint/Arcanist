#ifndef __Mote_hpp__
#define __Mote_hpp__
#include <stdint.h>
#include <utility>
#include <bitset>
#include <string>

#include <boost/array.hpp>
#include "util/HexDim.hpp"

namespace Wand 
{
static const int NUM_COMPONENTS_PER_MOTE = 4;
static const int NUM_ELEMENTS = 6;

enum Element { Void, Chaos, Fire, Spark, Life, Flow };

struct Component
{
	Component(Element e = Void, uint8_t n = 0) : element(e), quality(n) {}

	Element element;
	uint8_t quality;

	uint32_t weight() { return 1; }
	operator Element() const { return element; }
};

struct Mote
{
	typedef boost::array<Component, NUM_COMPONENTS_PER_MOTE> array_component;
	std::size_t size;
	array_component components;
	std::bitset<NUM_ELEMENTS> elements;

	typedef std::pair<int,int> point_type;
	point_type position;

	template<typename Comp>
	bool add(const Comp& c);

	uint32_t weight();

};

template<typename Comp>
bool Mote::add(const Comp& c)
{
	if(size == NUM_COMPONENTS_PER_MOTE)
		return false;

	components[size++] = c;
	elements[c] = true;
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
