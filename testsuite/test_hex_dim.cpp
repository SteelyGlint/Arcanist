#include <util/HexDim.hpp>

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>                                                    
#include <tuple>

#include <cmath>
#include <complex>
                                                                      
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
                                                                      
namespace bg=boost::geometry;                                         
namespace bgm=boost::geometry::model;                                 


using namespace wand::hex;
using wand::hex::detail::HexagonDim;




void print_info(const HexagonDim &h)
{
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout << "ISQRT: " << HexagonDim::SQRT_3 << std::endl
				 << "R:  " << h.Radius() << std::endl
	          << "W:  " << h.Width() << std::endl
	          << "HH: " << h.HalfHeight() << std::endl
	          << "H:  " << h.Height() << std::endl
	          << "S:  " << h.Side() << std::endl;
}

int main()
{
	constexpr HexagonDim hex(27.f);

	static_assert(std::isnormal(HexagonDim::SQRT_3),"height is not normal");

	static_assert(std::isnormal(hex.Height()),"height is not normal");
	static_assert(std::isnormal(hex.Radius()),"radius is not normal");
	static_assert(std::isnormal(hex.Width()),"width is not normal");
	static_assert(std::isnormal(hex.Side()),"side is not normal");
	static_assert(std::isnormal(hex.HalfHeight()),"side is not normal");
	static_assert(same(hex.Radius()*2.f,hex.Width()),"width dimensions are not the same.");
	static_assert(same(hex.HalfHeight(),hex.Height()/2.f),"height dimensions are not the same.");


	print_info(hex);





	return 0;
}
