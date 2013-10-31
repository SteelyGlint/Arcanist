#ifndef __HexSpace_hpp__
#define __HexSpace_hpp__

#include <iostream>
#include <stdexcept>
#include <utility>
#include <tuple>

#include <type_traits>

#include <cmath>

#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
//#include <boost/geometry/geometries/adapted/c_array.hpp>
//#include <boost/geometry/geometries/adapted/std_pair_as_segment.hpp>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;

//BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(bg::cs::cartesian)

#include "HexDim.hpp"

namespace wh=wand::hex;
namespace whd=wand::hex::detail;

constexpr whd::HexagonDim hex(27.f);
constexpr float SQRT_3 = whd::HexagonDim::SQRT_3;
constexpr float FLT_PREC = whd::HexagonDim::FLT_PREC;

constexpr float R = hex.Radius();
constexpr float W = hex.Width();
constexpr float HALF_H = hex.HalfHeight();
constexpr float H = hex.Height();
constexpr float S = hex.Side();




enum HexSide { NORTHWEST, NORTH, NORTHEAST, SOUTHEAST, SOUTH, SOUTHWEST };

bgm::segment< bgm::d2::point_xy<float> > hex_side(bgm::ring<bgm::d2::point_xy<float> > const &h, HexSide s);

#include "HexSpaceDebug.hpp"

constexpr inline float round_two(float f)
{
	return std::floor(0.5f + (f / FLT_PREC)) * FLT_PREC;
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

template<typename DEBUGPOLICY = NoVerifyHexRing>
struct THexPolygonGen
{
	typedef bgm::d2::point_xy<float> point;
	typedef bgm::ring<point> ring_type;

	template<typename Point>
	inline ring_type operator()(const Point& p)
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
/*
		std::vector<point> pts;
		pts.reserve(7);
		pts.emplace_back(_x - R    , _y);
		pts.emplace_back(_x - R/2.f, _y + HALF_H);
		pts.emplace_back(_x + R/2.f, _y + HALF_H);
		pts.emplace_back(_x + R    , _y);
		pts.emplace_back(_x + R/2.f, _y - HALF_H);
		pts.emplace_back(_x - R/2.f, _y - HALF_H);
		pts.emplace_back(_x - R    , _y);
*/
		ring_type hex_ring(std::begin(pts),std::end(pts)); // order of points matters.. must be clockwise.

		DEBUGPOLICY::verify(hex_ring);
		return hex_ring;
	}
};


typedef THexPolygonGen<> HexPolygonGen;

template<size_t SIDE>
struct hex_side_dispatch {};

template<>
struct hex_side_dispatch<NORTHWEST> 
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<float> >
	apply(bgm::ring<bgm::d2::point_xy<float> > const &h)
	{
		return seg_type(h[0],h[1]);
	}
};

template<>
struct hex_side_dispatch<NORTH> 
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<float> >
	apply(bgm::ring<bgm::d2::point_xy<float> > const &h)
	{
		return seg_type(h[1],h[2]);
	}
};

template<>
struct hex_side_dispatch<NORTHEAST> 
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<float> >
	apply(bgm::ring<bgm::d2::point_xy<float> > const &h)
	{
		return seg_type(h[2],h[3]);
	}
};

template<>
struct hex_side_dispatch<SOUTHEAST> 
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<float> >
	apply(bgm::ring<bgm::d2::point_xy<float> > const &h)
	{
		return seg_type(h[3],h[4]);
	}
};

template<>
struct hex_side_dispatch<SOUTH> 
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<float> >
	apply(bgm::ring<bgm::d2::point_xy<float> > const &h)
	{
		return seg_type(h[4],h[5]);
	}
};

template<>
struct hex_side_dispatch<SOUTHWEST> 
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<float> >
	apply(bgm::ring<bgm::d2::point_xy<float> > const &h)
	{
		return seg_type(h[5],h[6]);
	}
};




bgm::segment< bgm::d2::point_xy<float> > hex_side(bgm::ring<bgm::d2::point_xy<float> > const &h, const HexSide s)
{
	typedef bgm::segment< bgm::d2::point_xy<float> > seg_type;
	assert(bg::num_points(h) == 7);

	switch(s)
	{
		case NORTHWEST:
			return hex_side_dispatch< NORTHWEST >::apply(h);
			break;
		case NORTH:
			return hex_side_dispatch< NORTH >::apply(h);
			break;
		case NORTHEAST:
			return hex_side_dispatch< NORTHEAST >::apply(h);
			break;
		case SOUTHEAST:
			return hex_side_dispatch< SOUTHEAST >::apply(h);
			break;
		case SOUTH:
			return hex_side_dispatch< SOUTH >::apply(h);
			break;
		case SOUTHWEST:
			return hex_side_dispatch< SOUTHWEST >::apply(h);
			break;
	};

	assert(false);
	return seg_type({-1.f,-1.f},{-1.f,-1.f});
}



typedef bgm::d2::point_xy<float> point;



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


struct Hexagon
{
	typedef bgm::d2::point_xy<float> point_type;
	typedef bgm::ring<point_type> ring_type;
	typedef bgm::box<point_type> box_type;

	Hexagon(float x, float y)
		: hex_center{x,y},
		  hex_ring{HexPolygonGen{}(x,y)} {}
	
	float getX() const { return bg::get<0>(hex_center); }
	float getY() const { return bg::get<1>(hex_center); }
	ring_type const & getRing() const { return hex_ring; }

	box_type getBB() const 
	{ 
		box_type bb;
		bg::envelope(hex_ring,bb);
		return bb;
	}


	private:
	point     hex_center;
	ring_type hex_ring;

};


template<std::size_t ROWS, std::size_t COLS>
struct Hexagrid
{
	std::size_t n_rows;
	std::size_t n_cols;

	typedef bgm::d2::point_xy<float> hex_point_type;

	//Hexagon grid[ROWS][COLS];
//	char memory[sizeof(Hexagon)*ROWS*COLS];

	Hexagon *p_grid[ROWS*COLS];
	bgm::box<hex_point_type> m_bbox;

	Hexagon const& operator()(std::size_t x_r, std::size_t x_c) const
	{
		return *((Hexagon *)(p_grid[x_r*ROWS + x_c]));
	}

	Hexagrid()
		: n_rows(ROWS), n_cols(COLS),m_bbox(bg::make_inverse< bgm::box<hex_point_type> >())
	{
		memset(p_grid,'\0',sizeof(p_grid));

		for(std::size_t i = 0; i < ROWS;++i)
		{
			for(std::size_t j = 0; j < COLS;++j)
			{
				Hexagon *h = new 
					Hexagon( j * ((3* R)/2), ((j%2)* HALF_H) + (2*i*HALF_H));

				p_grid[i*ROWS + j] = h;

				bg::expand(m_bbox,h->getBB());
			}
		}
	}


	~Hexagrid()
	{
		for(std::size_t i = 0; i < ROWS;++i)
		{
			for(std::size_t j = 0; j < COLS;++j)
			{
				Hexagon *h;
				if( ( h = p_grid[i*ROWS + j]) != 0)
				{
					p_grid[i*ROWS + j] = nullptr;
					delete h;
				}
			}
		}
		
	}


};





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
