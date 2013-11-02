#ifndef __Hexagrid_hpp__
#define __Hexagrid_hpp__

#include <cstdint>
#include <cassert>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/make.hpp>





namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;

namespace wand {
namespace hex {


template<typename T>
struct Hexagrid
{
	private:
	const std::size_t n_rows;
	const std::size_t n_cols;
	
	public:
	inline std::size_t rows() const 
	{
		return n_rows;
	}

	inline std::size_t cols() const 
	{
		return n_cols;
	}


	using hex_point_type = bgm::d2::point_xy<float>;
	using box_type = bgm::box<hex_point_type>;

// Hexagon grid[n_rows][n_cols];
//	char memory[sizeof(Hexagon)*n_rows*n_cols];

	Hexagon<T> **p_grid; //[n_rows*n_cols];
	box_type m_bbox;

	box_type getBB() const
	{
		return m_bbox;
	}

	Hexagon<T> const& operator()(std::size_t x_r, std::size_t x_c) const
	{
		assert(x_r < n_rows);
		assert(x_c < n_cols);
		return *((Hexagon<T> *)(p_grid[x_r*n_cols + x_c]));
	}

	THexPolygonGen<T> hex_dim;

	Hexagrid(std::size_t n_rows, std::size_t n_cols, THexPolygonGen<T> hgen = THexPolygonGen<T>{})
		: n_rows(n_rows), n_cols(n_cols),m_bbox(bg::make_inverse< box_type >()),hex_dim(hgen)
	{
		const float R = hex_dim.R;
		const float HALF_H = hex_dim.HALF_H;

		p_grid = new Hexagon<T>*[n_rows*n_cols];
		memset(p_grid,'\0',sizeof(p_grid)*(n_rows*n_cols));

		for(std::size_t i = 0; i < n_rows;++i)
		{
			for(std::size_t j = 0; j < n_cols;++j)
			{
				Hexagon<T> *h = new 
					Hexagon<T>(R + j * ((3* R)/2), HALF_H+ ((j%2)* HALF_H) + (2*i*HALF_H),hex_dim);

				p_grid[i*n_cols + j] = h;

				bg::expand(m_bbox,h->getBB());
			}
		}
	}


	~Hexagrid()
	{
		for(std::size_t i = 0; i < n_rows;++i)
		{
			for(std::size_t j = 0; j < n_cols;++j)
			{
				Hexagon<T> *h;
				if( ( h = p_grid[i*n_cols + j]) != 0)
				{
					p_grid[i*n_cols + j] = nullptr;
					delete h;
				}
			}
		}
		
		delete [] p_grid;
		p_grid = nullptr;
	}



};




} }




#endif
