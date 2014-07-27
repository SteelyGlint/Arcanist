#include <iostream>
#include <vector>
#include <deque>
#include <utility>

#include <cassert>
#include <cmath>

#include <boost/geometry.hpp>
#include <boost/geometry/geometry.hpp>

#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/ring.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/make.hpp>

//using namespace bg;
//using namespace bg::model;

namespace bg=boost::geometry;
namespace bgm=bg::model;

using point_type = bgm::d2::point_xy<float>;
using lineseg_type = bgm::segment<point_type>;


template<typename Point>
void list_coordinates(Point const& p)
{
    using bg::get;
    std::cout << "x = " 
				  << std::setw(10) << std::right 
				  << get<0>(p) 
				  << std::setw(3) << std::left
				  << " y = " 
				  << std::setw(10) << std::right 
				  << get<1>(p) << std::endl;
}

template <typename Tag> struct dispatch {};

// Specialization for points
template <> struct dispatch<bg::point_tag>
{
    template <typename Point>
    static inline void apply(Point const& p)
    {
        // Use the Boost.Geometry free function "get"
        // working on all supported point types
        std::cout << "Hello POINT, you are located at: "
            << bg::get<0>(p) << ", "
            << bg::get<1>(p)
            << std::endl;
    }
};

template <> struct dispatch<bg::multi_point_tag>
{
    template <typename MultiPoint>
    static inline void apply(MultiPoint & mp)
    {
        // Use the Boost.Geometry free function "get"
        // working on all supported point types
        std::cout << "Hello Multi-POINT, you are located ats: ";

			int i = 0;
		  for( auto & pt : mp)
			{
				std::cout << i++ << ": " << bg::dsv(pt) << std::endl;
			}
    }
};

// Specialization for polygons
template <> struct dispatch<bg::polygon_tag>
{
    template <typename Polygon>
    static inline void apply(Polygon const& p)
    {
        // Use the Boost.Geometry manipulator "dsv" 
        // working on all supported geometries
        std::cout << "Hello POLYGON, you look like: "
            << bg::dsv(p)
            << std::endl;
    }
};

// Specialization for multipolygons
template <> struct dispatch<bg::multi_polygon_tag>
{
    template <typename MultiPolygon>
    static inline void apply(MultiPolygon const& m)
    {
        // Use the Boost.Range free function "size" because all
        // multigeometries comply to Boost.Range
        std::cout << "Hello MULTIPOLYGON, you contain: "
            << boost::size(m) << " polygon(s)"
            << std::endl;
    }
};

template <> struct dispatch<bg::segment_tag>
{
    template <typename Polygon>
    static inline void apply(Polygon const& p)
    {
        // Use the Boost.Geometry manipulator "dsv" 
        // working on all supported geometries
        std::cout << "Hello segment, you look like: "
            << bg::dsv(p)
            << std::endl;
    }
};

template <typename Geometry>
inline void hello(Geometry const& geometry)
{
    // Call the metafunction "tag" to dispatch, and call method (here "apply")
    dispatch
        <
            typename bg::tag<Geometry>::type
        >::apply(geometry);
}




template<typename LineSeg>
void print_ring_info(LineSeg &r)
{

	hello(r);
}





int main(int argc, char *argv[])
{
	return 0;
}


