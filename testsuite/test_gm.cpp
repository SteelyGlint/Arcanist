#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

namespace bg=boost::geometry;

struct my_point
{
    double x, y;
};

struct my_box
{
    my_point ll, ur;
};

// Register the point type
BOOST_GEOMETRY_REGISTER_POINT_2D(my_point, double, cs::cartesian, x, y)

// Register the box type, also notifying that it is based on "my_point"
BOOST_GEOMETRY_REGISTER_BOX(my_box, my_point, ll, ur)

int main()
{
    my_box b = boost::geometry::make<my_box>(100, 10, 1, 0);
    std::cout << "Area: "  << boost::geometry::area(b) << std::endl;
	 std::cout << "Points: " << bg::dsv(b) << std::endl;
	 bg::correct(b);
    std::cout << "Area: "  << boost::geometry::area(b) << std::endl;
	 std::cout << "Points: " << bg::dsv(b) << std::endl;

    return 0;
}
