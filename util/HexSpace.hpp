#ifndef __HexSpace_hpp__
#define __HexSpace_hpp__


#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(bg::cs::cartesian)

constexpr float SQRT_3 = 1.73205080757f;
constexpr float R = 27.f;
constexpr float W = R*2.f;
constexpr float HALF_H = R*SQRT_3/2.f;
constexpr float H = SQRT_3*R;

constexpr float S = (R*3.f)/2.f;

constexpr float FLT_PREC = 0.0001f;


enum HexSide { NORTHWEST, NORTH, NORTHEAST, SOUTHEAST, SOUTH, SOUTHWEST };
bgm::segment< bgm::d2::point_xy<float> > hex_side(bgm::ring<bgm::d2::point_xy<float> > const &h, HexSide s);

#include "HexSpaceDebug.hpp"

inline float round_two(float f)
{
	return floorf(0.5f + (f / FLT_PREC)) * FLT_PREC;
}


/*
	A HexPolygon is composed of 6 equalatieral triangles of radius R.
   Width of the cell is 2*R.
*/


/*
  Computes the vertex of the hexcell at the given coordinate (x,y)

|---R---|
|- - - W - - -|  W = 2 * R


    -------          ---
   /       \          |  
  /         \         |  
 /           \        |  
/    (x,y)    \       | H = 2 * (S )  
\             /       |     ---
 \           /        |      | HALF_H = cos ( 30 ) * R 
  \         /         |      |        = ( sqrt(3) / 2 ) * R
   \       /          |      |        = SQRT_3 / 2 * R
    -------          ---    ---

|----S----|

S is used when converting an point coordinate i,j into a hexcell

The size coordinates of the cell centered at (x,y) are:

(    x +/- R,  y             )
(    x - R/2,  y  +/- HALF_H )
(    x + R/2,  y  +/- HALF_H )
*/
#include <HexCell.hpp>

/*
	@param DEBUGPOLICY
		AssertVerifyHexRing - Checks the constructed hexring's num_points, and area
		NoVerifyHexRing     - no sanity checks
*/

template<typename DEBUGPOLICY = AssertVerifyHexRing>
struct THexPolygonGen
{
	typedef bgm::d2::point_xy<float> point;
	typedef bgm::ring<point> ring_type;

	inline ring_type operator()(const point& p)
	{ return (*this)(bg::get<0>(p),bg::get<1>(p)); }

	inline ring_type operator()(float x,float y)
	{

		float _x = round_two(x);
		float _y = round_two(y);
		
		std::vector<point> pts{ 
			{_x - R    , _y}, 
			{_x - R/2.f, round_two(_y + HALF_H) },
			{_x + R/2.f, round_two(_y + HALF_H) },
			{_x + R    , _y},
			{_x + R/2.f, round_two(_y - HALF_H) },
			{_x - R/2.f, round_two(_y - HALF_H) },
			{_x - R    , _y}, // enclosing point for correct ring type
		};

		ring_type hex_ring(std::begin(pts),std::end(pts)); // order of points matters.. must be clockwise.

		DEBUGPOLICY::verify(hex_ring);
		return hex_ring;
	}
};


typedef THexPolygonGen<> HexPolygonGen;


bgm::segment< bgm::d2::point_xy<float> > hex_side(bgm::ring<bgm::d2::point_xy<float> > const &h, HexSide s)
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;
	assert(bg::num_points(h) == 7);

	switch(s)
	{
		case NORTHWEST:
			return seg_type(h[0],h[1]);
			break;
		case NORTH:
			return seg_type(h[1],h[2]);
			break;
		case NORTHEAST:
			return seg_type(h[2],h[3]);
			break;
		case SOUTHEAST:
			return seg_type(h[3],h[4]);
			break;
		case SOUTH:
			return seg_type(h[4],h[5]);
			break;
		case SOUTHWEST:
			return seg_type(h[5],h[6]);
			break;
	};

	assert(false);
	return seg_type({-1.f,-1.f},{-1.f,-1.f});
}

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
struct HexCoordinate
{
	typedef bgm::d2::point_xy<float> point;
	point p;

	point South()
	{
		return point(bg::get<0>(p),bg::get<1>(p) - H);
	}

	point North()
	{
		return point(bg::get<0>(p),bg::get<1>(p) + H);
	}

	point SouthEast()
	{
		return point(bg::get<0>(p) + R*3.f/2.f, bg::get<1>(p) - HALF_H);
	}

	point SouthWest()
	{
		return point(bg::get<0>(p) - R*3.f/2.f, bg::get<1>(p) - HALF_H);
	}

	point NorthEast()
	{
		return point(bg::get<0>(p) + R*3.f/2.f, bg::get<1>(p) + HALF_H);
	}

	point NorthWest()
	{
		return point(bg::get<0>(p) - R*3.f/2.f, bg::get<1>(p) + HALF_H);
	}
};

#endif
