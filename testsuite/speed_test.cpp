// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#define _HAS_ITERATOR_DEBUGGING 0

#include <cassert>

#include <iostream>
#include <algorithm>
#include <forward_list>
#include <chrono>
#include <utility>

#include <vector>
#include <time.h>

#include <random>
#include <map>

#include <boost/geometry/geometry.hpp>

#include <util/HexSpace.hpp>

using std::cout;
using std::endl;
using std::forward_list;

using std::vector;
using std::map;

using std::make_pair;
using std::pair;

void ClockStart();
void ClockEnd();

typedef THexPolygonGen<NoVerifyHexRing> HexRingGen;
typedef HexRingGen::point point_type;

namespace bg=boost::geometry;

vector<point_type> CreateCommonAccessPattern(int size,float w = 10,float h = 10)
{
	ClockStart();
	vector<point_type> idx_vec(size);
	
	std::random_device rd;
	std::uniform_real_distribution<float> uniform_dist_w(0,w);
	std::uniform_real_distribution<float> uniform_dist_h(0,h);

	for(int i(0);i < size;++i)
		bg::assign_values(idx_vec[i],uniform_dist_w(rd),uniform_dist_h(rd));

	std::cout << "Create Random Accessing array ";
	ClockEnd();

	return idx_vec;
}

typedef std::chrono::high_resolution_clock my_clock;
my_clock::time_point t;
my_clock::time_point t_end;

void ClockStart()
{	
	t = my_clock::now();
}
void ClockEnd()
{ 
	using namespace std::chrono;
	t_end = my_clock::now();


	seconds s_duration = duration_cast<seconds>(t_end - t);
	milliseconds ms_duration = duration_cast<milliseconds>(t_end - t);
	microseconds us_duration = duration_cast<microseconds>(t_end - t);
	nanoseconds ns_duration = duration_cast<nanoseconds>(t_end - t);

	if(s_duration.count() >= 50)
	{
		cout << s_duration.count() << " s\n";
	}
	else if(ms_duration.count() >= 50)
	{
		cout << ms_duration.count() << " ms\n";
	} else if( us_duration.count() >= 50) {
		cout << us_duration.count() << " us\n";
	} else {
		cout << ns_duration.count() << " ns\n";
	}


}


template<std::size_t ROW, std::size_t COL>
class AccessExperiment
{
	public:
	Hexagrid<ROW,COL> hgrid;

	vector<point_type> access_idx;
	int size;

	explicit
	AccessExperiment(int _size = 10000)
		: hgrid(), access_idx(CreateCommonAccessPattern(_size,W*ROW,H*COL)), size(_size)
	{
	}

	void clock_hgrid_bb_check()
	{
		typedef Hexagon::box_type hex_box_type;
		hex_box_type hbbox = hgrid.getBB();


		int success = 0;
		ClockStart();
		for(auto const &p : access_idx)
		{
			if(bg::covered_by(p,hbbox))
				++success;
		}
		ClockEnd();

		std::printf("%d / %d random points were contained in the hexagrid bbox\n", success, size);
	}

}; 



int main()
{
	ClockStart();
	AccessExperiment<10,10> ex;
	ex.clock_hgrid_bb_check();
}
