#include <iostream>
#include <typeinfo>
#include <utility>
#include <cassert>
#include <util/SDL_BoostGeomPoint.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/geometry/strategies/transform/map_transformer.hpp>

#include <HexCell.hpp>
#include <util/Hex.hpp>
#include <Mote.hpp>
#include <util/Demangler.hpp>

#include <SDL.h>
#include <SDL_image.h>
#include <GraphicalHexGrid.hpp>
#include <MoteMovementManager.hpp>



#include <assets/XPMLoader.hpp>
#include <assets/HexCellBorder.xpm>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;


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


typedef bgm::d2::point_xy<float> hex_point_type;
typedef bgm::box<hex_point_type> hex_box_type;
typedef bgm::ring<hex_point_type> hex_ring_type;

typedef bgm::d2::point_xy<int> pixel_point_type;
typedef bgm::box<pixel_point_type> pixel_box_type;
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
		typedef bgm::segment<
				bgm::d2::point_xy<int>
			 > segment_type;


		SDL_SetRenderDrawColor(rend,255,128,255,255);
		for(std::size_t i = 0;i < n_points-1;++i)
		{
			draw(rend,segment_type(r[i],r[i+1]));
		}


		bgm::d2::point_xy<int> center_pt;
		bg::centroid(r,center_pt);
		SDL_SetRenderDrawColor(rend,34,34,34,255);

		for(std::size_t i = 0;i < n_points-1;++i)
		draw(rend,segment_type(r[i],center_pt));
		//draw(rend,segment_type(r[2],center_pt));
		//draw(rend,segment_type(r[4],center_pt));
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






void test_main(SDL_Window *win, SDL_Renderer *rend)
{
	using bg::dsv;

	constexpr std::size_t b_rows = 2;
	constexpr std::size_t b_cols = 1;

	int win_w, win_h;
	SDL_GetWindowSize(win,&win_w,&win_h);

	assert(TheHexGrid::Instance()->init(win_w,win_h,b_rows,b_cols,rend));

	TheHexGrid::Instance()->draw();

	SDL_Delay(2000);



}


