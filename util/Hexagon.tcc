#ifndef __Hexagon_tcc__
#define __Hexagon_tcc__

#include <boost/geometry/algorithms/envelope.hpp>

namespace wand {
namespace hex {

/*
	HexCoordinate is used to compute the coordinates of the neighbor
	hex from an origin:
---               -----        ---
   \   North     /              |
    \           /               |
North\         /                |
 West \-------/     North       H
      /       \       East      |
     /         \                |
    /           \               |
   /   HexCoord  \              |
---       p       -------      ---
   \             / 
    \           / 
South\         /    
West  \       /     South
      /-------\     East
     /         \
    /  South    \
   /             \
---


|--------| 1/2R + R

*/





template<typename T>
struct Hexagon
{
	using point_type = bgm::d2::point_xy<T>;
	using ring_type = bgm::ring<point_type>;
	using box_type = bgm::box<point_type>;

	Hexagon(T x, T y, THexPolygonGen<T> hgen);
	
	T getX() const;
	T getY() const;

	ring_type const & getRing() const;
	box_type getBB() const;

	private:
	point_type    hex_center;
	ring_type     hex_ring;

};




template<typename T>
inline Hexagon<T>::Hexagon(T x, T y, THexPolygonGen<T> hgen)
	: hex_center{x,y},
	  hex_ring(hgen(x,y)) {}


template<typename T>
inline T Hexagon<T>::getX() const 
{ 
  return bg::get<0>(hex_center); 
}

template<typename T>
inline T Hexagon<T>::getY() const 
{
  return bg::get<1>(hex_center); 
}

template<typename T>
typename Hexagon<T>::ring_type const & Hexagon<T>::getRing() const 
{ 
	return hex_ring;
}

template<typename T>
typename Hexagon<T>::box_type Hexagon<T>::getBB() const
{ 
	box_type bb;
	bg::envelope(hex_ring,bb);
	return bb;
}

} }
#endif
