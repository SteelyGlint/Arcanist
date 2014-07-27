#ifndef __GraphicalHexGrid_hpp__
#define __GraphicalHexGrid_hpp__
#include <utility>
#include <SDL.h>
#include "util/Hex.hpp"
#include "HexCell.hpp"

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;



namespace Wand
{

typedef bgm::d2::point_xy<int> pixel_point_type;
typedef bgm::box<pixel_point_type> pixel_box_type;
typedef bgm::ring<pixel_point_type> pixel_ring_type;



class HexGrid
{
	using hexgrid_type = wand::hex::Hexagrid<float>;
public:
	bool init(int w, int h,int rows, int cols, SDL_Renderer *sdlrender);
	void draw();

	HexIndex atPoint(int x, int y);

	static HexGrid* Instance() 
	{
		if(s_pInstance == 0)
			s_pInstance = new HexGrid();

		return s_pInstance;
	}
	
private:
	std::unique_ptr<hexgrid_type> m_pHexGrid;
	std::unique_ptr<HexCell> m_pHexCell;
	unsigned int hex_width = 0, hex_height = 0;
	int win_w, win_h;
	HexIndex m_dim;

	HexIndex m_hilited;

public:
	HexIndex const & dim() const { return m_dim; }
	unsigned int get_hex_width() const { return hex_width; }
	unsigned int get_hex_height() const { return hex_height; }

	void hilite_hex_at_coords(std::pair<int, int> pt);

private:
	HexGrid() = default;
	~HexGrid() = default;

	SDL_Renderer *rend;
	static HexGrid * s_pInstance;
};

}

typedef Wand::HexGrid TheHexGrid;
#endif
