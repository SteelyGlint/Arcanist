#ifndef __HexSpace_hpp__
#define __HexSpace_hpp__

#include <iostream>
#include <stdexcept>
#include <utility>


#include <cmath>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/assign.hpp>

#include "HexDim.hpp"

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;


namespace wand {
namespace hex {
namespace detail {



/*
	flat <--> pointy

swapping the input coordinates (i.e. "mirror" them around the diagonal): x<->y or i<->j;
applying the formulas as described above;
swapping the output coordinates back ("unmirroring" them): i<->j, x<->y.
*/
	template<typename T, typename Point>
	static inline std::vector<Point> fill_points_flat(T _x, T _y, T HALF_H, T R)
	{
		//bg::assign_value(points[0], $`typename detail::param<Point>::type value`)

		Point points[7];


		bg::assign_values(points[0],_x - R    , _y);
		bg::assign_values(points[1],_x - R/2.f, _y + HALF_H );
		bg::assign_values(points[2],_x + R/2.f, _y + HALF_H );
		bg::assign_values(points[3],_x + R    , _y);
		bg::assign_values(points[4],_x + R/2.f, _y - HALF_H );
		bg::assign_values(points[5],_x - R/2.f, _y - HALF_H );
		bg::assign_values(points[6],_x - R    , _y);

		std::vector<Point> pts(points,points+sizeof(points) / sizeof(Point) );
		return pts;
	}


/*
	template<typename T, typename Point = bgm::d2::point_xy<T> >
	static inline std::vector<Point> fill_points_pointy(T _x, T _y, T HALF_H, T R)
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

*/

} /* namespace detail */


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
//private:
	const float R;// = hex.Radius();
	const float W;// = hex.Width();
	const float HALF_H;// = hex.HalfHeight();
	const float H;/// = hex.Height();
	const float S;// = hex.Side();

	typedef HexagonDim dim_type;

public:

	THexPolygonGen(dim_type hex = dim_type(27.0f))
	: R(hex.Radius()), W(hex.Width()), HALF_H(hex.HalfHeight()), H(hex.Height()), S(hex.Side()) { }

	inline float round_two(float f)
	{
		return std::floor(0.5f + (f / detail::FLT_PREC)) * detail::FLT_PREC;
	}

public:
	typedef bgm::d2::point_xy<T> point_type;
	//using point_type = bgm::d2::point_xy<T>;
	typedef bgm::ring<point_type> ring_type;
	//using ring_type = bgm::ring<point_type>;

	template<typename Point>
	inline ring_type operator()(const Point& p)
	{ return (*this)(bg::get<0>(p),bg::get<1>(p)); }

	inline ring_type operator()(T x,T y)
	{
		std::vector<point_type> pts = 
			detail::fill_points_flat<T,point_type>(x,y, HALF_H, R);
		ring_type hex_ring(pts.begin(),pts.end()); // order of points matters.. must be clockwise.
		return hex_ring;
	}


};



} }


#endif
