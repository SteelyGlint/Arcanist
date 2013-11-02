
#ifndef __HexSpaceDebug_hpp__
#define __HexSpaceDebug_hpp__

#include <cassert>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/length.hpp>

//#include <boost/geometry/geometries/adapted/c_array.hpp>
//#include <boost/geometry/geometries/adapted/std_pair_as_segment.hpp>
//BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(bg::cs::cartesian)

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;

namespace wand {
namespace hex {


/*
	specialiazation when constructing HexPolygonGen
*/
template<typename HDIM>
struct AssertVerifyHexRing
{
	template<typename HexRing>
	static bool verify(const HexRing &hex_ring, const HexagonDim &hex_dim)
	{
		const float H = hex_dim.Height();
		const float R = hex_dim.Radius();

		bool ret = true;
		assert(::boost::geometry::num_points(hex_ring) == 7);

		assert(bg::area(hex_ring) >= 0);
		std::cout << "Area Should be: " << (H/2.f)*R*3.f << std::endl;
		std::cout << "Area Is: " << bg::area(hex_ring) << std::endl;

		assert(abs(((H/2.f)*R*3.f) - bg::area(hex_ring)) <= 0.0001f);

		bgm::segment<typename bg::point_type<HexRing>::type> seg;

		float s_len = bg::length(seg(hex_ring[0],hex_ring[1]));

//		float s_len = bg::length(hex_side(hex_ring,static_cast<HexSide>(0)));
//		for(int i = 0;i < 6;++i)
//		{
//			assert(fabs(fabs(s_len) - fabs(bg::length(hex_side(hex_ring,static_cast<HexSide>(i))))) <= 0.0001f);
//		}
		return ret;
	}

};



} }

#endif
