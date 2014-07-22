/*
	This program creates a polygon at a specified coordinate.  The motemanager
   uses the genereated polygon to test if a mote's next position update should 
   trigger any callbacks.  This example file demonstrates the core functionality.


	TODO:: generate a multipolygon with the border's the wand culled out.  motemanager can use 
   the contains() function to test if the mote has a valid global coordinate.

	TODO:: Use polygon to render in opengel instead of using SDL and XPM pixel data?

	TODO:: use global offsets and scaling to manipulate the display window of the hexgrid by user.
	


Sample Output:



Hex (0,0)

x =         27 y =    23.3827
x =          0 y =    23.3827
x =       13.5 y =    46.7654
x =       40.5 y =    46.7654
x =         54 y =    23.3827
x =       40.5 y =          0
x =       13.5 y =          0
x =          0 y =    23.3827
Bounding box of hexring: ((0, 0), (54, 46.7654))
Area Should be: 1894
Area Is: 1894
Hex (1,0) ( SOUTHEAST )

x =       67.5 y =    46.7654
x =       40.5 y =    46.7654
x =         54 y =    70.1481
x =         81 y =    70.1481
x =       94.5 y =    46.7654
x =         81 y =    23.3827
x =         54 y =    23.3827
x =       40.5 y =    46.7654
Bounding box of hexring: ((40.5, 23.3827), (94.5, 70.1481))
Area Should be: 1894
Area Is: 1894
Hex (0,1) ( SOUTH )

x =         27 y =    70.1481
x =          0 y =    70.1481
x =       13.5 y =    93.5307
x =       40.5 y =    93.5307
x =         54 y =    70.1481
x =       40.5 y =    46.7654
x =       13.5 y =    46.7654
x =          0 y =    70.1481
Bounding box of hexring: ((0, 46.7654), (54, 93.5307))
Area Should be: 1894
Area Is: 1894
Mote Position #0
x =         27 y =    23.3827
Mote within hex_0_0
Mote Position #1
x =    36.4038 y =    31.5266
Mote within hex_1_0
Mote Position #2
x =    45.8075 y =    39.6705
Mote within hex_1_0
Mote Position #3
x =    55.2113 y =    47.8144
Mote within hex_1_0
Mote Position #4
x =     64.615 y =    55.9582
Mote within hex_1_0
Mote Position #5
x =    74.0188 y =    64.1021
Mote Position #6
x =    83.4225 y =     72.246




*/


#include <iostream>
#include <vector>
#include <deque>
#include <utility>

#include <cassert>
#include <cmath>

#include <boost/geometry.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/make.hpp>


#include "HexSpace.hpp"

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;


const char* s_dir[] =
{
	"NORTHWEST",
	"NORTH",
	"NORTHEAST",
	"SOUTHEAST",
	"SOUTH",
	"SOUTHWEST"
};



template<typename Point>
void list_coordinates(Point const& p)
{
    std::cout << "x = " 
				  << std::setw(10) << std::right 
				  << bg::get<0>(p) 
				  << std::setw(3) << std::left
				  << " y = " 
				  << std::setw(10) << std::right 
				  << bg::get<1>(p) << std::endl;
}

template<typename HexRing>
void print_ring_info(HexRing& r)
{
	using ring_type = typename bg::ring_type<HexRing>::type;
	using point_type = typename bg::point_type<ring_type>::type;


	//std::cout << "Size: " << r.size() << std::endl;
	std::cout << bg::dsv(r) << std::endl;

	//typename ring_type::iterator it,it_next;

/*
	int i = 0;
	for(int i = 0; i < 6;++i)
	{
		std::cout << "Side " << s_dir[i] << std::endl;
		list_coordinates(r[i]);
		list_coordinates(r[i+1]);
	}
*/
	std::cout << std::setw(12) << std::left
		<< "NORTHWEST : " 
		<< std::setw(16) << std::right
		<< bg::dsv(hex_side(r,NORTHWEST)) << std::endl;

	std::cout << std::setw(12) << std::left
		<< "NORTH : " 
		<< std::setw(16) << std::right
		<< bg::dsv(hex_side(r,NORTH)) << std::endl;

	std::cout << std::setw(12) << std::left
		<< "NORTHEAST : " 
		<< std::setw(16) << std::right
		<< bg::dsv(hex_side(r,NORTHEAST)) << std::endl;

	std::cout << std::setw(12) << std::left
		<< "SOUTHEAST : " 
		<< std::setw(16) << std::right
		<< bg::dsv(hex_side(r,SOUTHEAST)) << std::endl;

	std::cout << std::setw(12) << std::left
		<< "SOUTH : " 
		<< std::setw(16) << std::right
		<< bg::dsv(hex_side(r,SOUTH)) << std::endl;

	std::cout << std::setw(12) << std::left
		<< "SOUTHWEST : " 
		<< std::setw(16) << std::right
		<< bg::dsv(hex_side(r,SOUTHWEST)) << std::endl;



	float s_len = bg::length(hex_side(r,static_cast<HexSide>(0)));
	for(int i = 0;i < 6;++i)
	{
		assert(fabs(fabs(s_len) - fabs(bg::length(hex_side(r,static_cast<HexSide>(i))))) <= 0.0001f);
	}


	//bg::for_each_point(r, list_coordinates<point_type>);

	assert(bg::area(r) >= 0);

	bgm::box<point_type> box;
	bg::envelope(r,box);
	
	std::cout << "Bounding box of hexring: " << bg::dsv(box) << std::endl;

}




/*

struct MoteMovement
{
	// float,float := position
	// vec<float,float>::normalized := bearing
   // vec<float,float>::velocity

	// next_pos = pos * vel

	// hexcell_id <i,j> := current cell id/coordinate
};

struct hexcell
{
	array i, j := hexgrid coordinate of cell;
	hex_ring		:= polygon of cell

	desired_pos<mote>::next_pos
   curr_hex         := hex_id

	if( bg::within(hex_ring[hex_id], next_pos) )
  // no change, update pos
       mote::pos <- next_pos
	else
	{
		side = get_line_corssed( next_pos, hex_ring )
*/



/*
http://stackoverflow.com/questions/9251537/how-to-create-a-boost-range-that-hides-multiple-layers-of-vectors-and-exposes-it/9252979#9252979
*/



int main(int argc, char *argv[])
{
	typedef bgm::d2::point_xy<float> point;
	typedef bgm::ring<point> ring_type;

	HexPolygonGen h_build;

	constexpr float x = 0.0f;
	constexpr float y = 0.0f;

	HexCoordinate first{{x,y}};


	point orig[] = 
	{
		{first.p},
		{first.NorthWest()},
		{first.North()},
		{first.NorthEast()},
		{first.SouthEast()},
		{first.South()},
		{first.SouthWest()}

	};

	ring_type hex[] =
	{
		{h_build(orig[0])},
		{h_build(orig[1])},
		{h_build(orig[2])},
		{h_build(orig[3])},
		{h_build(orig[4])},
		{h_build(orig[5])},
		{h_build(orig[6])}
	};


	//for(int i = 1;i < 7;++i)
		//assert(!bg::intersects(hex[0],hex[i]));



	std::cout << "Hex (Origin) @ " << bg::dsv(orig[0]) << std::endl;
	print_ring_info(hex[0]);

	for(int i = 1;i <= 6;++i)
	{
		std::cout << "Hex ( " << s_dir[i-1] << " ) of origin @ " << bg::dsv(orig[i]) << std::endl;
		print_ring_info(hex[i]);
	}

	point mote_pos{first.p};

	assert( bg::covered_by(mote_pos, hex[0] ) );

	for(int i = 1;i < 7;++i)
		assert( ! bg::covered_by(mote_pos, hex[i] ) );

/*
	Compute unit vector for direction. 
	it is assigned to SouthEast, @ hex_1_0
*/
	const float dir_v_len{sqrt(W*W+H*H)};

	bool exit_now = false;
	for(int i = 0; i < 10;++i)
	{
		std::cout << "Mote Position #" << i << std::endl;
		list_coordinates(mote_pos);

		if(exit_now)
			return 0;


		/* find next point */
		point mote_new_pos(W/dir_v_len,H/dir_v_len);
		float vel = 12.00f;
		bg::multiply_value(mote_new_pos, vel);
		bg::add_point(mote_new_pos,mote_pos);

		bool mote_tracked = false;

		for(int i = 0;i < 7;++i)
		{
			if( bg::covered_by(mote_new_pos,hex[i]) )
			{
				std::cout << "Mote within hex " << (i == 0 ? "Center" : s_dir[i-1]) << std::endl;
				mote_tracked = true;
			}
		}


		if(!mote_tracked)
			exit_now = true;

		/* update location */
		bg::assign_values(mote_pos, bg::get<0>(mote_new_pos),bg::get<1>(mote_new_pos));
		
	}
	assert(false);


}
