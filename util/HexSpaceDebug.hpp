
#ifndef __HexSpaceDebug_hpp__
#define __HexSpaceDebug_hpp__
namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;

#include <cassert>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;


typedef bgm::d2::point_xy<float> point;
typedef bgm::ring<point> ring_type;



struct NoVerifyHexRing
{
	template<typename HexRing>
	static bool verify(const HexRing &hex_ring)
	{
		return true;
	}
};

struct AssertVerifyHexRing
{
	template<typename HexRing>
	static bool verify(const HexRing &hex_ring)
	{
		bool ret = true;
		assert(bg::num_points(hex_ring) == 7);

		assert(bg::area(hex_ring) >= 0);
		std::cout << "Area Should be: " << (H/2.f)*R*3.f << std::endl;
		std::cout << "Area Is: " << bg::area(hex_ring) << std::endl;

		assert(abs(((H/2.f)*R*3.f) - bg::area(hex_ring)) <= 0.0001f);

		float s_len = bg::length(hex_side(hex_ring,static_cast<HexSide>(0)));
		for(int i = 0;i < 6;++i)
		{
			assert(fabs(fabs(s_len) - fabs(bg::length(hex_side(hex_ring,static_cast<HexSide>(i))))) <= 0.0001f);
		}
		return ret;
	}

};



#endif
