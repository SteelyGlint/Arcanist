#include <iostream>

#include "util/SDL_BoostGeomPoint.hpp"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/geometry/strategies/transform/map_transformer.hpp>

#include "HexCell.hpp"
#include <util/Hex.hpp>


#include <SDL_image.h>
#include <assets/XPMLoader.hpp>
#include <assets/HexCellBorder.xpm>


#include "TextureManager.hpp"
#include "GraphicalHexGrid.hpp"

namespace bg = boost::geometry;
namespace bgm = boost::geometry::model;

namespace Wand {

HexGrid* HexGrid::s_pInstance = 0;

typedef bgm::d2::point_xy<float> hex_point_type;
typedef bgm::box<hex_point_type> hex_box_type;
typedef bgm::ring<hex_point_type> hex_ring_type;


bool HexGrid::init(int w, int h,int rows, int cols, SDL_Renderer *sdlrender)
{
	std::cerr << "Window Dimensions: " << w << 'x' << h << std::endl;
	std::cerr << "HexGrid Dimensions: " << cols << 'x' << rows << std::endl;

	rend = sdlrender;
	m_dim = std::make_pair(w,h);

	m_pHexGrid = std::unique_ptr<hexgrid_type>(new hexgrid_type(rows,cols));
	m_pHexCell = std::unique_ptr<HexCell>(new HexCell(sdlrender));
	
	win_w = w;
	win_h = h;

	bgm::box<hex_point_type> hexgrid_bbox;
	//m_pHexGrid->getBB();
	bg::assign(hexgrid_bbox, m_pHexGrid->getBB());

	std::cerr << "hexgrid bb: " << bg::dsv(hexgrid_bbox) << std::endl;
	

	return true;
}

HexIndex HexGrid::atPoint(int x, int y)
{
	std::cerr << "HexGrid::atPoint(" << x << ',' << y << std::endl;
	const int W = hex_width;
	const float R = W/2.000;
	const int S = (3.00*R)/2.00;
	const int H = (sqrt(3)*R);

	int i_t = floor(x/S);

	int y_ts = (float)y - (i_t%2)*(H/2);
	int j_t = floor(y_ts/H);


	int x_t = x - i_t * S;
	int y_t = y_ts - j_t*H;

	int i = (x_t > R*abs(0.500 - y_t/H)) ? i_t : i_t - 1;
	int j = (x_t > R*abs(0.500 - y_t/H)) ? j_t : j_t - i%2 + ((y_t > H/2) ? 1 : 0);

	return HexIndex(i,j);
}

void HexGrid::draw()
{
	HexCell *tCell = m_pHexCell.get();
	auto to_pixel = m_pHexGrid->hexRingToPixelMapper(win_w,win_h);

	unsigned int b_rows = m_pHexGrid->rows();
	unsigned int b_cols = m_pHexGrid->cols();

	auto render_func = [&tCell](const pixel_ring_type &pixel_ring)
	{ 
		//std::cerr << "pixel_ring: " << bg::dsv(pixel_ring) << std::endl;
		SDL_BBox destCell;
		bg::envelope(pixel_ring,destCell);
		{
			SDL_Rect destRect((SDL_Rect)destCell);
			tCell->draw(destRect);
		}
	};

	//renderOnce = true;
	to_pixel(render_func);
}




} /*namespace Wand */
