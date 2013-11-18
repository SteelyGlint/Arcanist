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
	using hex_point_type = bgm::d2::point_xy<float>;
	using box_type = bgm::box<hex_point_type>;
private:
	Hexagon<T> **p_grid;
	box_type m_bbox;
	THexPolygonGen<T> hex_dim;

	const float f_off_x;
	const float f_off_y;
public:
	inline float offset_x() const { return f_off_x; }
	inline float offset_y() const { return f_off_y; }

	inline std::size_t rows() const 
	{
		return n_rows;
	}

	inline std::size_t cols() const 
	{
		return n_cols;
	}
	
	inline
	const THexPolygonGen<T> &dim() const
	{
		return hex_dim;
	}

	box_type getBB() const
	{
		return m_bbox;
	}

	Hexagon<T> const& operator()(std::size_t x_r, std::size_t x_c) const
	{
		assert(x_r < n_rows);
		assert(x_c < n_cols);
		return *((Hexagon<T> *)(p_grid[x_c*n_rows + x_r]));
	}


	Hexagrid(std::size_t n_rows, std::size_t n_cols, THexPolygonGen<T> hgen = THexPolygonGen<T>{})
		: n_rows(n_rows), n_cols(n_cols),m_bbox(bg::make_inverse< box_type >()),hex_dim(hgen), f_off_x(hex_dim.R), f_off_y(hex_dim.HALF_H)
	{
		const float R = hex_dim.R;
		const float HALF_H = hex_dim.HALF_H;

		p_grid = new Hexagon<T>*[n_rows*n_cols];
		memset(p_grid,'\0',sizeof(p_grid)*(n_rows*n_cols));

		for(std::size_t i = 0; i < n_rows;++i)
		{
			for(std::size_t j = 0; j < n_cols;++j)
			{
	/*			--flat orientation-- */
				Hexagon<T> *h = new 
					Hexagon<T>(f_off_x + j * ((3* R)/2), f_off_y + ((j%2)* HALF_H) + (2*i*HALF_H),hex_dim); 
//					Hexagon<T>(j * ((3*R)/2), ((j%2)* HALF_H) + (2*i*HALF_H),hex_dim); 

	/*       --pointy orientation-- */
/*				Hexagon<T> *h = new 
					Hexagon<T>(HALF_H + (i%2)*HALF_H + 2*j*HALF_H,R + i * ((3*R)/2),hex_dim); 
*/

				p_grid[j*n_rows + i] = h;
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
				if( ( h = p_grid[j*n_rows + i]) != 0)
				{
					p_grid[i*n_cols + j] = nullptr;
					delete h;
				}
			}
		}
		
		delete [] p_grid;
		p_grid = nullptr;
	}


	private:
	class mapPointToHexCoord
	{
		const float R;
		const float S;
		const float H;

		//const float offset_x;
		//const float offset_y;

		public:

		constexpr mapPointToHexCoord(float Rad, float Sid, float Hei) : R(Rad), S(Sid), H(Hei) { }

//		mapPointToHexCoord()
//			: R(this->dim().R), S(dim().S), H(dim().H) { }

		std::pair<int,int> operator()(hex_point_type p)
		{
			//os << "Point: (" <<  bg::get<0>(p) << ',' << bg::get<1>(p);
			float x = bg::get<0>(p),
					y = bg::get<1>(p);


			int i_t = floorf(x / S);

			float y_ts = y - (i_t%2)*(H/2.f);
			int j_t = floorf(y_ts/H);


			float x_t = x - i_t*S;
			float y_t = y_ts - j_t*H;


			int i = x_t > R*fabsf(0.5f - y_t/H) ? i_t : i_t - 1;
			int j = x_t > R*fabsf(0.5f - y_t/H) ? j_t : j_t - i%2 + (y_t > H/2.f ? 1 : 0);
			
			//os << " maps to hex (" << j << ',' << i << ") ";

			return std::pair<int,int>(i,j);
		}
	};

	public:
	mapPointToHexCoord pointToHexMapper() { return mapPointToHexCoord{dim().R,dim().S,dim().H}; }

	


};




} }




#endif
