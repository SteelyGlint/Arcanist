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
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <cstdlib>

#include <map>

#include <utility>
#ifdef __linux__
#include <sys/time.h>
#else
#include <time.h>
#endif

#include <boost/tuple/tuple.hpp>
#include <boost/geometry/geometry.hpp>


#include <util/Hex.hpp>

using std::cout;
using std::endl;

using std::vector;
using std::map;

using std::make_pair;
using std::pair;
using std::rand;

void ClockStart();
void ClockEnd();

typedef wand::hex::THexPolygonGen<float> HexRingGen;
typedef HexRingGen::point_type point_type;

namespace bg=boost::geometry;

static float randflt(int LO, int HI)
{
	return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}	



vector<point_type> CreateCommonAccessPattern(int size,float w = 10,float h = 10)
{
	ClockStart();
	vector<point_type> idx_vec(size);
	
//	std::random_device rd;
//	std::uniform_real_distribution<float> uniform_dist_w(0,w);
//	std::uniform_real_distribution<float> uniform_dist_h(0,h);

	for(int i(0);i < size;++i)
	{
		float rand_w = randflt(0,w);
		float rand_h = randflt(0,h);

		bg::assign_values(idx_vec[i],rand_w,rand_h);
	}

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

	wand::hex::Hexagrid<float>::box_type h_bb = hgrid.getBB();

	float min_w = bg::get<bg::min_corner,0>(h_bb);
	float max_w = bg::get<bg::max_corner,0>(h_bb);

	float min_h = bg::get<bg::min_corner,1>(h_bb);
	float max_h = bg::get<bg::max_corner,1>(h_bb);
	

	for(int i(0);i < size;++i)
	{
		float rnd_w = randflt(min_w,max_w);
		float rnd_h = randflt(min_h,max_h);
		bg::assign_values(idx_vec[i],rnd_w,rnd_h);
	}



	std::cout << "Initialize " << size << " random points from (" 
			<< min_w << " - " << max_w
			<< ','
			<< min_h << " - " << max_h 
			<< "): ";
	ClockEnd();


	return idx_vec;
}


//typedef std::chrono::high_resolution_clock my_clock;
//my_clock::time_point t;
//my_clock::time_point t_end;

struct timeval t;
struct timeval t_end;

void ClockStart()
{	
	gettimeofday(&t,NULL);
}
void ClockEnd()
{ 
	gettimeofday(&t_end,NULL);
	struct timeval result;
	timersub(&t_end,&t,&result);

	cout << result.tv_sec << " s" << result.tv_usec << " ms\n";
}


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

		wand::hex::Hexagrid<float>::box_type hbbox = hgrid.getBB();
		std::cout << "Timing bounding box covered_by: ";

		int success = 0;
		ClockStart();
		
		for(vector<point_type>::iterator it = access_idx.begin(); it != access_idx.end();++it)
		{
			if(bg::covered_by((*it),hbbox))
				++success;
		}
		ClockEnd();

		if(success != size)
			std::printf("%d / %d random points were contained in the hexagrid bbox\n", success, size);
	}

	void clock_hgrid_pointlookup_verify()
	{
		//auto toHex(hgrid.pointToHexMapper());

		std::cout << "Timing point to hexagon-id _verify_: ";
		ClockStart();
		for(vector<point_type>::iterator it = access_idx.begin(); it != access_idx.end();++it)
		{

			std::pair<int,int> hex_coord = hgrid.toHex(*it);

			int i_row = hex_coord.second;
			int i_col = hex_coord.first;
			int id = i_col * m_rows+ i_row;

			if(  i_row >= 0 && i_row < m_rows && i_col >= 0 && i_col < m_cols )
			{
				 assert(bg::covered_by(*it,hgrid(i_row,i_col).getRing()));
			}
	
		}
		ClockEnd();
	}

	void clock_hgrid_pointlookup()
	{
		wand::hex::Hexagrid<float>::mapPointToHexCoord toHex(hgrid.pointToHexMapper());

		std::cout << "Timing point to hexagon-id: ";
		ClockStart();
		for(vector<point_type>::iterator it = access_idx.begin(); it != access_idx.end();++it)
		{
			std::pair<int,int> hex_coord = toHex(*it);

			int i_row = hex_coord.second;
			int i_col = hex_coord.first;

			int id = i_col * m_rows+ i_row;

			if(  i_row >= 0 && i_row < m_rows && i_col >= 0 && i_col < m_cols )
			{
				bg::covered_by(*it,hgrid(i_row,i_col).getRing());
			}
	
		}

		ClockEnd();

	}


	void clock_hgrid_pointlookup_naive()
	{
		ClockStart();
		for(vector<point_type>::iterator it = access_idx.begin(); it != access_idx.end();++it)
		{
			for(std::size_t i = 0; i < m_rows;++i)
			{
				for(std::size_t j = 0; j < m_cols;++j)
				{
					if(bg::covered_by((*it),hgrid(i,j).getRing()))
					{
						std::size_t volatile id = i*m_cols + j;
						goto success;
					}
				}
			}

			success:
				continue;
		}


		std::cout << "Timing point to hexagon-id (naive): ";
		ClockEnd();
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
	ex.clock_hgrid_pointlookup_verify();
	//ex.clock_hgrid_pointlookup_naive();
}
