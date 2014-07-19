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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include <assets/XPMLoader.hpp>
#include <assets/HexCellBorder.xpm>

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
			segment_type seg;
			bg::assign_point(seg.first,r[i]);
			bg::assign_point(seg.second,r[i+1]);
			draw(rend,seg);
		}


		bgm::d2::point_xy<int> center_pt;
		bg::centroid(r,center_pt);
		SDL_SetRenderDrawColor(rend,34,34,34,255);

		for(std::size_t i = 0;i < n_points-1;++i)
		{
			segment_type seg;
			bg::assign_point(seg.first,r[i]);
			bg::assign_point(seg.second,center_pt);

			draw(rend,seg);
		}
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

static SDL_Renderer* rend = 0;

void setRenderer(SDL_Renderer* r)
{
	rend = r;
}


void test_draw(const pixel_ring_type &pixel_ring)
{
	HexCell tCell(rend);

	SDL_BBox destCell;
	bg::envelope(pixel_ring,destCell);
	{
		SDL_Rect destRect((SDL_Rect)destCell);
		tCell.draw(destRect);
	}
	std::cerr << "Render to box: " << bg::dsv(destCell) << std::endl;
}



void test_main(SDL_Window *win, SDL_Renderer *rend)
{
	using bg::dsv;

	std::size_t b_rows = 11;
	std::size_t b_cols = 11;

	wand::hex::Hexagrid<float> b(b_rows,b_cols);

	bgm::box<hex_point_type> hexgrid_bbox;
	bg::assign(hexgrid_bbox,b.getBB());

	std::cout << "hexgrid bb" << dsv(hexgrid_bbox) << std::endl;

	int win_w, win_h;
	SDL_GetWindowSize(win,&win_w,&win_h);
	std::cout << "Window width: " << win_w
		  << " height: " << win_h << std::endl;


	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);

	setRenderer(rend);

	SDL_Surface* pSurface = IMG_ReadXPMFromArray((char **)&HexCell_xpm);
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(rend,pSurface);

//	wand::hex::Hexagrid<float>::mapHexToPixel to_pixel = b.hexRingToPixelMapper(win_w,win_h);
//	to_pixel(&test_draw);


	trans::map_transformer<int,2,2,true,true> map_hex_to_pixel(hexgrid_bbox,win_w,win_h);

	for(std::size_t i = 0; i < b_rows;++i)
	{
		for(std::size_t j = 0;j < b_cols;++j)
		{
			hex_ring_type dest_hexcell_ring;
			assert(bg::transform(b(i,j).getRing(),dest_hexcell_ring,map_hex_to_pixel));
			draw(rend,dest_hexcell_ring);

			SDL_BBox destCell;
			bg::envelope(dest_hexcell_ring,destCell);

			{
					
				SDL_Rect destRect((SDL_Rect)destCell);
				SDL_RenderCopy(rend,pTexture,NULL,&destRect);
			}
		}
	}
	SDL_RenderPresent(rend);
	SDL_Delay(2000);


	SDL_DestroyTexture(pTexture);
}


