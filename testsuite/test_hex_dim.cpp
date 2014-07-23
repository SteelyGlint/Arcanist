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

using std::cout;
using std::endl;
using std::vector;


void print_info(const HexagonDim &h)
{
	cout.setf( std::ios::fixed, std:: ios::floatfield );
	cout << "Hexagon properties:\n";
	cout << "sqrt(3): " << detail::SQRT_3 << endl
	          << "radius:  " << h.Radius() << endl
	          << "width:  " << h.Width() << endl
	          << "halfheight: " << h.HalfHeight() << endl
	          << "height:  " << h.Height() << endl
	          << "side:  " << h.Side() << endl;
}

void print_info(const bgm::d2::point_xy<float> &point)
{
	cout.setf( std::ios::fixed, std:: ios::floatfield );
	cout << '(' << point.x() 
	     << ',' << point.y() << ')';
}


/***
	Prints the coordinates of the points of a hexagon.
	Can specifiy offset coordinate offset of the hexagon origin with -x or -y
	Can change the default radius of the hexagon with -r
 
*/

int main(int argc, char *argv[])
{
#if defined __linux__ && 0
	constexpr HexagonDim hex{27.f};
	static_assert(std::isnormal(detail::SQRT_3),"height is not normal");
	static_assert(std::isnormal(hex.Height()),"height is not normal");
	static_assert(std::isnormal(hex.Radius()),"radius is not normal");
	static_assert(std::isnormal(hex.Width()),"width is not normal");
	static_assert(std::isnormal(hex.Side()),"side is not normal");
	static_assert(std::isnormal(hex.HalfHeight()),"side is not normal");
	static_assert(same(hex.Radius()*2.f,hex.Width()),"width dimensions are not the same.");
	static_assert(same(hex.HalfHeight(),hex.Height()/2.f),"height dimensions are not the same.");
#endif

	int iarg = 1;

	
	using Point = bgm::d2::point_xy<float>;

	float R = 27.f;

	float _x = 0.f;
	float _y = 0.f;

	for(; iarg < argc; ++iarg)
	{
		if( !argv[iarg] || argv[iarg][0] == '\0')
			break;

		if( argv[iarg] && argv[iarg][0] == '-' && argv[iarg][1])
		{
			if(!argv[iarg + 1] || argv[iarg + 1][0] == '\0')
				continue;
			switch (argv[iarg][1])
			{
				case 'r':
					R = atof(argv[iarg+1]);
					break;
				case 'x':
					_x = atof(argv[iarg+1]);
					break;
				case 'y':
					_y = atof(argv[iarg+1]);
					break;

			}
		}
	}



	HexagonDim hex{R};

	print_info(hex);

	float HALF_H = hex.HalfHeight();
	cout << "Hexagon origin: (" << _x << ',' << _y << ')' << endl;

	std::vector<Point> hex_pts{ 
		{_x - R    , _y}, 
		{_x - R/2.f, _y + HALF_H },
		{_x + R/2.f, _y + HALF_H },
		{_x + R    , _y},
		{_x + R/2.f, _y - HALF_H },
		{_x - R/2.f, _y - HALF_H },
		{_x - R    , _y}, 		// enclosing point for correct ring type
	};

	cout << "Points: ";
	for( auto &p : hex_pts )
	{
		print_info(p);
		cout << ' ';
	}

	return 0;
}
