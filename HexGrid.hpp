#ifndef __HexGrid_hpp__
#define __HexGrid_hpp__
#include <utility>

using HexIndex = std::pair<int,int>;

class HexGrid
{
public:
	bool init(int w, int h);
	void draw();

	HexIndex atPoint(int x, int y);

	static HexGrid* Instance() 
	{
		if(s_pInstance == 0)
			s_pInstance = new HexGrid();

		return s_pInstance;
	}
	
private:
	SDL_Texture *pHexTexture = NULL;
	uint hex_width = 0, hex_height = 0;
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

typedef HexGrid TheHexGrid;
#endif
