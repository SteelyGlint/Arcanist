#ifndef __HexCell_hpp__
#define __HexCell_hpp__
namespace Wand
{
	using HexIndex = std::pair<uint8_t,uint8_t>;
	class HexCell
	{
		SDL_Renderer *m_rend;
		SDL_Texture *m_texture;
		public:
		HexCell(SDL_Renderer *);
		void draw(SDL_Rect const &dest) const;
	};

};

#endif
