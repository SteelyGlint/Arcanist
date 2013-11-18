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

#include <cstdio>
#include <climits>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <forward_list>
#include <chrono>
#include <utility>

#include <vector>
#include <time.h>

#include <random>
#include <map>

#include <boost/geometry/geometry.hpp>

#include <util/Hex.hpp>

using std::cout;
using std::endl;
using std::forward_list;

using std::vector;
using std::map;

using std::make_pair;
using std::pair;

void ClockStart();
void ClockEnd();

typedef wand::hex::THexPolygonGen<float> HexRingGen;
typedef HexRingGen::point_type point_type;

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

	std::cout << "Initialize " << size << " random points from (0 - " << w << ",0 - " << h << "): ";
	ClockEnd();

	return idx_vec;
}

vector<point_type> CreateCommonAccessPattern(int size,wand::hex::Hexagrid<float> &hgrid)
{
	std::cout << "Radius: " << hgrid.dim().R
             << std::endl
			    << "Side:   " << hgrid.dim().S
             << std::endl
			    << "Height: " << hgrid.dim().H
             << std::endl
             << "off_X:  " << hgrid.offset_x()
             << std::endl
             << "off_Y:  " << hgrid.offset_y()
             << std::endl

             << std::endl;

	ClockStart();
	vector<point_type> idx_vec(size);

	auto h_bb = hgrid.getBB();

	auto min_w = bg::get<bg::min_corner,0>(h_bb);
	auto max_w = bg::get<bg::max_corner,0>(h_bb);

	auto min_h = bg::get<bg::min_corner,1>(h_bb);
	auto max_h = bg::get<bg::max_corner,1>(h_bb);
	
	
	std::random_device rd;
	std::uniform_real_distribution<float> uniform_dist_w(min_w,max_w);
	std::uniform_real_distribution<float> uniform_dist_h(min_h,max_h);

	for(int i(0);i < size;++i)
		bg::assign_values(idx_vec[i],uniform_dist_w(rd),uniform_dist_h(rd));



	std::cout << "Initialize " << size << " random points from (" 
			<< min_w << " - " << max_w
			<< ','
			<< min_h << " - " << max_h 
			<< "): ";
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

/*
class mapPointToHexCoord
{
	const float R;
	const float S;
	const float H;

	const float offset_x;
	const float offset_y;

	public:

	mapPointToHexCoord(const wand::hex::Hexagrid<float>& hgrid)
		: R(hgrid.dim().R), S(hgrid.dim().S), H(hgrid.dim().H), offset_x(hgrid.offset_x()), offset_y(hgrid.offset_y()) { }

	std::pair<int,int> operator()(point_type p, std::ostream &os)
	{
		os << "Point: (" <<  bg::get<0>(p) << ',' << bg::get<1>(p);
		float x = bg::get<0>(p),
			   y = bg::get<1>(p);


		int i_t = floorf(x / S);

		float y_ts = y - (i_t%2)*(H/2.f);
		int j_t = floorf(y_ts/H);


		float x_t = x - i_t*S;
		float y_t = y_ts - j_t*H;


		int i = x_t > R*fabsf(0.5f - y_t/H) ? i_t : i_t - 1;
		int j = x_t > R*fabsf(0.5f - y_t/H) ? j_t : j_t - i%2 + (y_t > H/2.f ? 1 : 0);
		
		os << " maps to hex (" << j << ',' << i << ") ";

		return std::pair<int,int>(i,j);
	}
};
*/



class AccessExperiment
{
	public:
	const std::size_t m_rows;
	const std::size_t m_cols;
	wand::hex::Hexagrid<float> hgrid;

	int size;
	vector<point_type> access_idx;

	explicit
	AccessExperiment(std::size_t a_row = 1, std::size_t a_col = 1, int _size = 100000) 
		: m_rows(a_row), m_cols(a_col), hgrid(m_rows,m_cols), size(_size)
	{
		std::printf("Initialize hexagrid %ld x %ld: ",m_rows,m_cols);
		ClockEnd();
		ClockStart();
		access_idx = CreateCommonAccessPattern(size,hgrid);
	}

	void clock_hgrid_bb_check()
	{
		auto hbbox = hgrid.getBB();
		std::cout << "Timing bounding box covered_by: ";

		int success = 0;
		ClockStart();
		for(auto const &p : access_idx)
		{
			if(bg::covered_by(p,hbbox))
				++success;
		}
		ClockEnd();

		if(success != size)
			std::printf("%d / %d random points were contained in the hexagrid bbox\n", success, size);
	}

	void clock_hgrid_pointlookup()
	{
		std::vector<int> hist(m_rows*m_cols,0);

		int bounds_failure = 0;
		auto toHex(hgrid.pointToHexMapper());


		std::cout << "Timing point to hexagon-id: ";
		ClockStart();
		for(auto const &p : access_idx)
		{
			std::pair<int,int> hex_coord = toHex(p);

			int i_row = std::get<1>(hex_coord);
			int i_col = std::get<0>(hex_coord);

			int id = i_col * m_rows+ i_row;

			bool bounds_error = true;

			if(  i_row >= 0 && i_row < m_rows 
           && i_col >= 0 && i_col < m_cols )
			{

           bg::covered_by(p,hgrid(i_row,i_col).getRing());
			  ++hist[id];
			} else 
				++bounds_failure;
	
		}

		ClockEnd();

		if( bounds_failure )
			std::cout << "(error bounds " << bounds_failure << ") ";
		std::cout << std::endl;


	}


	void clock_hgrid_pointlookup_naive()
	{
		std::vector<int> hist(m_rows*m_cols,0);

		int failure = 0;

		ClockStart();
		for(auto const &p : access_idx)
		{
			for(std::size_t i = 0; i < m_rows;++i)
			{
				for(std::size_t j = 0; j < m_cols;++j)
				{
					if(bg::covered_by(p,hgrid(i,j).getRing()))
					{
						std::size_t id = i*m_cols + j;
						++hist[id];
						goto success;
					}
				}
			}

			++failure;

			success:
				continue;
		}


		std::cout << "Timing point to hexagon-id (naive): ";
		std::cout << "(failed " << failure << "): ";
		ClockEnd();

		auto result = std::minmax_element(hist.begin(),hist.end());
		std::vector<float> weighted_hist(hist.begin(),hist.end());

		const int run_size = this->size;

		std::for_each(weighted_hist.begin(),weighted_hist.end(),
			[failure,run_size, result](float &f)
		{
			f /= *result.second;
			f *= 10.0f + (40.0f * static_cast<float>(failure)/run_size);
		});


		for(std::size_t i = 0;i < weighted_hist.size();++i)
		{
			auto cnt = hist[i];
			if(cnt)
				std::printf("hex %-4ld %-4d: %s\n", i, cnt,std::string(weighted_hist[i],'*').c_str());
		}
	}


}; 

void read_env(const char* pChar, std::size_t& value)
{
	if(!pChar)
		return;

	std::size_t temp = strtoul(pChar,NULL,0);
	if(temp != 0L)
	{
		if(temp == ULONG_MAX)
		{
			perror("error reading environment variable!");
		} else {
			value = temp;
		}
	}
}


int main()
{
	std::size_t n_rows = 4;
	std::size_t n_cols = 2;
	std::size_t n_pts = 100000;

	read_env(std::getenv("ROWS"),n_rows);
	read_env(std::getenv("COLS"),n_cols);
	read_env(std::getenv("POINTS"),n_pts);

	ClockStart();
	AccessExperiment ex(n_rows,n_cols,n_pts);
	ex.clock_hgrid_bb_check();
	ex.clock_hgrid_pointlookup();
	ex.clock_hgrid_pointlookup_naive();
}
