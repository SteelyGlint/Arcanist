#ifndef __GlyphController_hpp__
#define __GlyphController_hpp__
#include "HexGrid.hpp"
#include "Glyph.hpp"
#include <map>

using namespace Glyph;

class GlyphController
{
	protected:
	std::map<HexIndex,Glyph::GlyphGraphicalObject> m_mapGlyph;

	public:
	bool debugGlyphs();


	bool placeGlyph(HexIndex loc, Glyph_Type g_type = Glyph_Type::Extract);

	bool init();

	void clean();
	
	void update();

	void draw();

	static GlyphController* Instance()
	{
		if(s_pInstance == 0)
			s_pInstance = new GlyphController();

		return s_pInstance;
	}


	private:
	GlyphController() = default;
	~GlyphController() = default;
	static GlyphController *s_pInstance;
	
};

typedef GlyphController TheGlyphController;

#endif
