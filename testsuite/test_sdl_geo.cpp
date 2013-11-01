#include <iostream>
#include <typeinfo>
#include <utility>
#include <cassert>
#include <util/SDL_BoostGeomPoint.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

#include <util/HexSpace.hpp>
#include <Mote.hpp>

#include <SDL.h>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;

using namespace Wand;

std::ostream& operator<<(std::ostream &os, SDL_BBox &b)
{
	os << '('
	   << std::setw(4)
      << bg::get<0>(b.ll)
		<< ','
	   << std::setw(4)
      << bg::get<1>(b.ll)
		<< ") -> ("
	   << std::setw(4)
		<< bg::get<0>(b.ur)
		<< ','
	   << std::setw(4)
      << bg::get<1>(b.ur)
		<< ')'
      << std::endl;

	return os;
}


typedef THexPolygonGen<NoVerifyHexRing> HexRingGen;
typedef THexPolygonGen<NoVerifyHexRing>::point hex_point_type;

typedef bgm::ring<hex_point_type> hex_ring_type;

typedef bgm::d2::point_xy<int> pixel_point_type;
typedef bgm::ring<pixel_point_type> pixel_ring_type;


namespace trans=boost::geometry::strategy::transform;


template<typename Geometry>
inline void draw(SDL_Renderer *rend, Geometry const & geometry);



template<typename Tag> struct render_dispatch {};


template<> struct render_dispatch<bg::point_tag>
{
	template <typename Point>
	static inline void apply(SDL_Renderer *rend, Point const& p)
	{
		if(SDL_RenderDrawPoint(rend,bg::get<0>(p),bg::get<1>(p)) < 0)
		{
			std::cout << SDL_GetError() << std::endl;
		}
	}

};
	

template<> struct render_dispatch<bg::segment_tag>
{
	template <typename Segment>
	static inline void apply(SDL_Renderer *rend, Segment const& s)
	{
		if(SDL_RenderDrawLine(rend,
			bg::get<0,0>(s),
			bg::get<0,1>(s),
			bg::get<1,0>(s),
			bg::get<1,1>(s)) < 0)
		{
			std::cout << SDL_GetError() << std::endl;
		}

	}
};




template<> struct render_dispatch<bg::ring_tag>
{
	template <typename Ring>
	static inline void apply(SDL_Renderer *rend, Ring const& r)
	{
		std::size_t n_points = bg::num_points(r);
//		std::cout << "render_ring (num points " << n_points << "): " << bg::dsv(r) << std::endl;

		for(std::size_t i = 0;i < n_points-1;++i)
		{
			typedef bgm::segment<
					bgm::d2::point_xy<int>
				 > segment_type;

			draw(rend,segment_type(r[i],r[i+1]));
		}
	}
};

template<> struct render_dispatch<bg::polygon_tag>
{
	template <typename Polygon>
	static inline void apply(SDL_Renderer *rend, Polygon const& p)
	{
		std::size_t n_irings = bg::num_interior_rings(p);
		std::cout << "render_polygon (int rings " << n_irings << "): " << bg::dsv(p) << std::endl;
		draw(rend,p.outer());
	}
};


template<typename Geometry>
inline void draw(SDL_Renderer *rend, Geometry const & geometry)
{
	render_dispatch<
		typename bg::tag<Geometry>::type
	>::apply(rend,geometry);
}

inline void draw(SDL_Renderer *rend, Mote const &m)
{

	if(SDL_RenderDrawPoint(rend,bg::get<0>(m.position),bg::get<1>(m.position)) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}

}







void test_main(SDL_Window *win, SDL_Renderer *rend)
{
	using bg::dsv;

	constexpr std::size_t b_rows = 8;
	constexpr std::size_t b_cols = 2;

	Hexagrid<b_rows,b_cols> b;

	bgm::box<hex_point_type> hexgrid_bbox;
	bg::assign(hexgrid_bbox,b.m_bbox);

	std::cout << "hexgrid bb" << dsv(hexgrid_bbox) << std::endl;

	int win_w, win_h;
	SDL_GetWindowSize(win,&win_w,&win_h);
	std::cout << "Window widith: " << win_w
				 << " height: " << win_h << std::endl;


	trans::map_transformer<hex_point_type,pixel_point_type,true,true> map_hex_to_pixel(hexgrid_bbox,win_w,win_h);

	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);


	SDL_SetRenderDrawColor(rend,255,128,255,255);
	for(std::size_t i = 0; i < b_rows;++i)
	{
		for(std::size_t j = 0;j < b_cols;++j)
		{
			pixel_ring_type dest_hexcell_ring;
			assert(bg::transform(b(i,j).getRing(),dest_hexcell_ring,map_hex_to_pixel));
			draw(rend,dest_hexcell_ring);
		}
	}

	SDL_RenderPresent(rend);
	SDL_Delay(2000);

}


#if 0
void test_main2(SDL_Window *win, SDL_Renderer *rend)
{
	HexRingGen hGen;

	SDL_Point p1{0,0};


	typedef bg::point_type<SDL_BBox>::type sdl_point_type;
	typedef bgm::d2::point_xy<float> hex_point_type;

	hex_ring_type hexcell_ring(hGen(p1));

	hex_ring_type hexcell_ring2(hGen(55,35));


// Get BBox of hexring Polygon
	bgm::box<hex_point_type> hbox;
	bgm::box<hex_point_type> hbox2;

	bg::envelope(hexcell_ring,hbox);
	bg::envelope(hexcell_ring2,hbox2);

	using bg::dsv;

	std::cout << "hex polygon: " << dsv(hexcell_ring) << std::endl;
	std::cout << "bounding box: " << dsv(hbox) << std::endl;

	std::cout << "hex polygon2: " << dsv(hexcell_ring2) << std::endl;
	std::cout << "bounding box: " << dsv(hbox2) << std::endl;

	int win_w, win_h;
	SDL_GetWindowSize(win,&win_w,&win_h);
	std::cout << "Window widith: " << win_w
				 << " height: " << win_h << std::endl;


	bgm::box<hex_point_type> hexgrid_bbox = bg::make_inverse< bgm::box< hex_point_type> >();;


	bg::expand(hexgrid_bbox, hbox);
	bg::expand(hexgrid_bbox, hbox2);


	trans::map_transformer<hex_point_type,hex_point_type,true,true> map_hex_to_pixel(hexgrid_bbox,win_w,win_h);

	hex_ring_type dest_hexcell_ring;
	hex_ring_type dest_hexcell_ring2;

	assert(bg::transform(hexcell_ring,dest_hexcell_ring,map_hex_to_pixel));
	assert(bg::transform(hexcell_ring2,dest_hexcell_ring2,map_hex_to_pixel));

	std::cout << "dest hex polygon: " << dsv(dest_hexcell_ring) << std::endl;
	std::cout << "dest hex polygon2: " << dsv(dest_hexcell_ring2) << std::endl;

	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);

	SDL_SetRenderDrawColor(rend,255,128,255,255);
	draw(rend,dest_hexcell_ring);
	SDL_SetRenderDrawColor(rend,128,255,128,255);
	draw(rend,dest_hexcell_ring2);

	SDL_RenderPresent(rend);
	//SDL_Delay(5000);

}
#endif
