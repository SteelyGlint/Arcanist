#include <util/HexDim.hpp>

#include <Mote.hpp>
#include <memory>
#include <utility>

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>                                                    
#include <tuple>

#include <boost/geometry/io/dsv/write.hpp>

#include <GraphicalHexGrid.hpp>
#include <MoteMovementManager.hpp>

#include <cassert>

using namespace Wand;

const char *print_element(Element e)
{
	switch(e)
	{
		case Element::Void:
			return "Void";
		case Element::Chaos:
			return "Chaos";
		case Element::Fire:
			return "Fire";
		case Element::Spark:
			return "Spark";
		case Element::Life:
			return "Life";
		case Element::Flow:
			return "Flow";
	}

	assert(false);
	return NULL;
}
 
template<typename Mote>
void print_mote(const Mote &m);

template<typename Component>
void print_component(const Component &c)
{
		std::cout 
					 << std::right << std::setw(6)
					 << print_element(c)
					 << std::right << std::setw(4)
					 << ((uint32_t)c.quality)
					 << std::endl;

}

template<>
void print_mote<Mote>(const Mote &m)
{
	std::cout << "Mote (" << m.size << "): bf #"
				 << m.elements
				 << " @"
	//			 << boost::geometry::dsv(m.position) //broken
				 << std::endl;
	
	for(uint i = 0; i < m.size;++i)
	{
		std::cout << "Component " << i << ":";
		print_component(m.components[i]);
	}
}


int main(int argc, char *argv[])
{
	Mote m;
	print_mote(m);
	Component c1{Element::Fire,4};
	m.add(c1);
	m.add(Component{Element::Spark,1});
	print_mote(m);
}
