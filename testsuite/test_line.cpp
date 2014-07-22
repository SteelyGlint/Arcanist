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

//using namespace boost::geometry;
//using namespace boost::geometry::model;

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;



template<typename Point>
void list_coordinates(Point const& p)
{
    using boost::geometry::get;
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
template <> struct dispatch<boost::geometry::point_tag>
{
    template <typename Point>
    static inline void apply(Point const& p)
    {
        // Use the Boost.Geometry free function "get"
        // working on all supported point types
        std::cout << "Hello POINT, you are located at: "
            << boost::geometry::get<0>(p) << ", "
            << boost::geometry::get<1>(p)
            << std::endl;
    }
};


template <> struct dispatch<boost::geometry::multi_point_tag>
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
template <> struct dispatch<boost::geometry::polygon_tag>
{
    template <typename Polygon>
    static inline void apply(Polygon const& p)
    {
        // Use the Boost.Geometry manipulator "dsv" 
        // working on all supported geometries
        std::cout << "Hello POLYGON, you look like: "
            << boost::geometry::dsv(p)
            << std::endl;
    }
};

// Specialization for multipolygons
template <> struct dispatch<boost::geometry::multi_polygon_tag>
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

template <> struct dispatch<boost::geometry::segment_tag>
{
    template <typename Polygon>
    static inline void apply(Polygon const& p)
    {
        // Use the Boost.Geometry manipulator "dsv" 
        // working on all supported geometries
        std::cout << "Hello segment, you look like: "
            << boost::geometry::dsv(p)
            << std::endl;
    }
};



template <typename Geometry>
inline void hello(Geometry const& geometry)
{
    // Call the metafunction "tag" to dispatch, and call method (here "apply")
    dispatch
        <
            typename boost::geometry::tag<Geometry>::type
        >::apply(geometry);
}




template<typename LineSeg>
void print_ring_info(LineSeg &r)
{

	hello(r);
	//boost::geometry::for_each_segment(r, list_coordinates<point_type>);
}


int main(int argc, char *argv[])
{
	typedef boost::geometry::model::d2::point_xy<float> point_type;
	typedef boost::geometry::model::segment<point_type> lineseg_type;

	lineseg_type x(point_type(1,1),point_type(0,0));
	lineseg_type x2(point_type(1,0),point_type(0,1));

	print_ring_info(x);
	print_ring_info(x2);

	assert(bg::intersects(x,x2));

	std::deque<point_type> i_pts;


	if(bg::intersection(x,x2,i_pts))
	{
		std::cout << "Intersection!      ";

			int i;

		  for( auto & pt : i_pts)
			{
				std::cout << i++ << ": " << bg::dsv(pt) << std::endl;
			}

		//hello(i_pts);
		//list_coordinates(i_pt);
	}

	return 0;
}


