#ifndef __HexSpace_hpp__
#define __HexSpace_hpp__

#include <iostream>
#include <stdexcept>
#include <utility>
#include <tuple>

#include <type_traits>

#include <cmath>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include "HexDim.hpp"

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;


namespace wand {
namespace hex {
namespace space {

constexpr float SQRT_3 = ::wand::hex::detail::SQRT_3;
constexpr float FLT_PREC = ::wand::hex::detail::FLT_PREC;

constexpr HexagonDim hex(27.f);


}

namespace detail {

template<typename S>
struct hex_points;


template<>
struct hex_points<hex_shape_flat_tag>
{
	template<typename T, typename Point = bgm::d2::point_xy<T> >
	static inline std::vector<Point> apply(T _x, T _y, T HALF_H, T R)
	{
		std::vector<Point> pts{ 
			{_x - R    , _y}, 
			{_x - R/2.f, round_two(_y + HALF_H) },
			{_x + R/2.f, round_two(_y + HALF_H) },
			{_x + R    , _y},
			{_x + R/2.f, round_two(_y - HALF_H) },
			{_x - R/2.f, round_two(_y - HALF_H) },
			{_x - R    , _y}
		};

		return pts;
	}
};

template<>
struct hex_points<hex_shape_pointy_tag>
{

	template<typename T, typename Point = bgm::d2::point_xy<T> >
	static inline std::vector<Point> apply(T _x, T _y, T HALF_H, T R)
	{
		std::vector<Point> pts{ 
			{_x - HALF_H,   _y + R/2.f}, 
			{_x    , _y + R},
			{_x + HALF_H,   _y + R/2.f}, 
			{_x + HALF_H,   _y - R/2.f}, 
			{_x    , _y - R},
			{_x - HALF_H,   _y - R/2.f}, 
			{_x - HALF_H,   _y + R/2.f}

		};
		return pts;
	}


};


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


/*
	@param DEBUGPOLICY
		AssertVerifyHexRing - Checks the constructed hexring's num_points, and area
		NoVerifyHexRing     - no sanity checks
*/



template<typename T>
struct THexPolygonGen
{
private:
	const float R;// = hex.Radius();
	const float W;// = hex.Width();
	const float HALF_H;// = hex.HalfHeight();
	const float H;/// = hex.Height();
	const float S;// = hex.Side();

	typedef HexagonDim dim_type;

public:

	constexpr THexPolygonGen(dim_type hex = dim_type{27.0f})
	: R(hex.Radius()), W(hex.Width()), HALF_H(hex.HalfHeight()), H(hex.Height()), S(hex.Side()) { }

	constexpr inline float round_two(float f)
	{
		return std::floor(0.5f + (f / space::FLT_PREC)) * space::FLT_PREC;
	}

/*
	todo:
  use bg::point_traits
*/
public:
	using point_type = bgm::d2::point_xy<T>;
	using ring_type = bgm::ring<point_type>;
	using hex_type = hex_shape_flat_tag;

	template<typename Point>
	inline ring_type operator()(const Point& p)
	{ return (*this)(bg::get<0>(p),bg::get<1>(p)); }

	inline ring_type operator()(T x,T y)
	{

		T _x = round_two(x);
		T _y = round_two(y);
		
		std::vector<point_type> pts{
			detail::hex_points<hex_shape_pointy_tag>::apply(x,y, HALF_H, R)
		};
/*
		std::vector<point_type> pts;
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

//		DEBUGPOLICY::verify(hex_ring);
		return hex_ring;
	}
};



//template<typename T>
//using PointyHexPolygonGen=THexPolygonGen<T,hex_shape_pointy_tag>;

//template<typename T>
//using FlatHexPolygonGen=THexPolygonGen<T,hex_shape_flat_tag>;



//template PointyHexPolygonGen<float>;


} }


#endif
