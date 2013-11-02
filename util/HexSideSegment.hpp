#ifndef __HexSideSegment_hpp__
#define __HexSideSegment_hpp__

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;


namespace wand {
namespace hex {

namespace detail {

struct hex_shape_flat_tag {};
	enum HexSide { NORTHWEST, NORTH, NORTHEAST, SOUTHEAST, SOUTH, SOUTHWEST };

template<typename T, typename S, size_t SIDE>
struct hex_side_dispatch {};

template<typename T>
struct hex_side_dispatch<T,hex_shape_flat_tag,0> 
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<T> >
	apply(bgm::ring<bgm::d2::point_xy<T> > const &h)
	{
		return seg_type(h[0],h[1]);
	}
};

template<typename T>
struct hex_side_dispatch<T,hex_shape_flat_tag,1> 
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<T> >
	apply(bgm::ring<bgm::d2::point_xy<T> > const &h)
	{
		return seg_type(h[1],h[2]);
	}
};

template<typename T>
struct hex_side_dispatch<T,hex_shape_flat_tag,2> 
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<T> >
	apply(bgm::ring<bgm::d2::point_xy<T> > const &h)
	{
		return seg_type(h[2],h[3]);
	}
};

template<typename T>
struct hex_side_dispatch<T,hex_shape_flat_tag,3> 
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<T> >
	apply(bgm::ring<bgm::d2::point_xy<T> > const &h)
	{
		return seg_type(h[3],h[4]);
	}
};

template<typename T>
struct hex_side_dispatch<T,hex_shape_flat_tag,4> 
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<T> >
	apply(bgm::ring<bgm::d2::point_xy<T> > const &h)
	{
		return seg_type(h[4],h[5]);
	}
};

template<typename T>
struct hex_side_dispatch<T,hex_shape_flat_tag,5> 
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;

	static inline 
	bgm::segment< bgm::d2::point_xy<T> >
	apply(bgm::ring<bgm::d2::point_xy<T> > const &h)
	{
		return seg_type(h[5],h[6]);
	}
};


/*
template<typename T>
bgm::segment< bgm::d2::point_xy<T> > hex_side(bgm::ring<bgm::d2::point_xy<T> > const &h, const HexSide s)
{
	typedef bgm::segment< bgm::d2::point_xy<T> > seg_type;
	assert(bg::num_points(h) == 7);

	switch(s)
	{
		case NORTHWEST:
			return hex_side_dispatch<T,hex_shape_flat_tag, NORTHWEST >::apply(h);
			break;
		case NORTH:
			return hex_side_dispatch<T,hex_shape_flat_tag, NORTH >::apply(h);
			break;
		case NORTHEAST:
			return hex_side_dispatch<T,hex_shape_flat_tag, NORTHEAST >::apply(h);
			break;
		case SOUTHEAST:
			return hex_side_dispatch<T,hex_shape_flat_tag, SOUTHEAST >::apply(h);
			break;
		case SOUTH:
			return hex_side_dispatch<T,hex_shape_flat_tag, SOUTH >::apply(h);
			break;
		case SOUTHWEST:
			return hex_side_dispatch<T,hex_shape_flat_tag, SOUTHWEST >::apply(h);
			break;
	};

	assert(false);
	return seg_type;
}
*/

/*
template<typename T>
struct HexCoordinate
{
	typedef bgm::d2::point_xy<T> point;
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
*/




} } }


#endif
