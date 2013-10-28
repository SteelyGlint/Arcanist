#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/assign.hpp>

#include "HexSpace.hpp"


template<typename Point>
void list_coordinates(Point const& p)
{
    std::cout << "x = " 
				  << std::setw(10) << std::right 
				  << boost::geometry::get<0>(p) 
				  << std::setw(3) << std::left
				  << " y = " 
				  << std::setw(10) << std::right 
				  << boost::geometry::get<1>(p) << std::endl;
}



template <typename Segment>
struct print_segment
{
	print_segment() : n_seg(0) {}

    inline void operator()(Segment const& s)
    {
		  std::cout << "Segment:" << n_seg++ << std::endl;
        list_coordinates(s.first);
        list_coordinates(s.second);
    }

	private:
	uint n_seg;
};


int main()
{
    // Bring "+=" for a vector into scope
    using namespace boost::assign;

    // Define a type
    typedef HexPolygonGen::point point;
    typedef HexPolygonGen::ring_type ring_type;


	 HexPolygonGen hGen;
	 ring_type tHex = hGen(0,0);

    // Declare the gathering class...
	 print_segment
        <
            boost::geometry::model::referring_segment<point>
        > functor;

    // ... and use it, the essention.
    // As also in std::for_each it is a const value, so retrieve it as a return value.
    functor = boost::geometry::for_each_segment(tHex, functor);


    return 0;
}
