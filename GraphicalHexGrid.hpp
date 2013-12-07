#ifndef __HexGrid_hpp__
#define __HexGrid_hpp__
#include <utility>
#include <util/Hex.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

namespace bg=boost::geometry;
namespace bgm=boost::geometry::model;



namespace Wand
{

typedef bgm::d2::point_xy<int> pixel_point_type;
typedef bgm::box<pixel_point_type> pixel_box_type;
typedef bgm::ring<pixel_point_type> pixel_ring_type;



class HexGrid
{
	typedef wand::hex::Hexagrid<float> hexgrid_type;
public:
	bool init(int w, int h,int rows, int cols);
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
	uint hex_width = 0, hex_height = 0;
	int win_w, win_h;
	HexIndex m_dim;


public:
	HexIndex const & dim() const { return m_dim; }
	uint get_hex_width() { return hex_width; }
	uint get_hex_height() { return hex_height; }

private:
	HexGrid() = default;
	~HexGrid() = default;

	static HexGrid * s_pInstance;
};

}

typedef Wand::HexGrid TheHexGrid;
#endif
