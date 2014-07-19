#include <util/HexDim.hpp>

#include <iostream>
#include <util/Demangler.hpp>
#include <iomanip>
#include <utility>

#include <cmath>
#include <complex>
                                                                      
#include <boost/tuple/tuple.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>


#include <boost/mpl/vector_c.hpp>

                                                                      
namespace bg=boost::geometry;                                         
namespace bgm=boost::geometry::model;                                 


using namespace wand::hex;
using wand::hex::HexagonDim;




void print_info(const HexagonDim &h)
{
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout << "ISQRT: " << detail::SQRT_3 << std::endl
				 << "R:  " << h.Radius() << std::endl
	          << "W:  " << h.Width() << std::endl
	          << "HH: " << h.HalfHeight() << std::endl
	          << "H:  " << h.Height() << std::endl
	          << "S:  " << h.Side() << std::endl;
}

int main()
{
	::HexagonDim hex(27.f);

	//static_assert(std::isnormal(hex.HalfHeight()),"side is not normal");
	//static_assert(same(hex.Radius()*2.f,hex.Width()),"width dimensions are not the same.");
	//static_assert(same(hex.HalfHeight(),hex.Height()/2.f),"height dimensions are not the same.");


	print_info(hex);


	typedef boost::mpl::vector_c< std::size_t, 1, 2, 3, 4, 5>::type value_types;

	value_types v;
	std::cout << typeid(v) << std::endl;


#if 0 
	std::vector<point> pts{ 
		{_x - R    , _y}, 
		{_x - R/2.f, round_two(_y + HALF_H) },
		{_x + R/2.f, round_two(_y + HALF_H) },
		{_x + R    , _y},
		{_x + R/2.f, round_two(_y - HALF_H) },
		{_x - R/2.f, round_two(_y - HALF_H) },
		{_x - R    , _y}, // enclosing point for correct ring type
	};
#endif




	return 0;
}
