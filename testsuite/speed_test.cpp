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

typedef HexPolygonGen::point point_type;

namespace bg=boost::geometry;

vector<point_type> CreateCommonAccessPattern(int size,int w = 10,int h = 10)
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


template<typename KEY = int, typename VALUE = int,intmax_t TRIALS = 10000>
class AccessExperiment
{
	public:
	HexPolygonGen hGen;

	vector<point_type> access_idx;

	int size;
	explicit
	AccessExperiment(int _size = 10000)
		: access_idx(CreateCommonAccessPattern(_size)), size(_size)
	{

		ClockStart();
		for(auto const &p : access_idx)
		{
			hGen(bg::get<0>(p),bg::get<1>(p));
		}
		ClockEnd();

		ClockStart();
		for(auto const &p : access_idx)
		{
			hGen(p);
		}
		ClockEnd();


	}

}; 



int main()
{
	ClockStart();
	AccessExperiment<> ex;
}
