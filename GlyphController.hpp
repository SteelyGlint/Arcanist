#ifndef __GlyphController_hpp__
#define __GlyphController_hpp__
#include "HexCell.hpp"
#include "GlyphGraphicalObject.hpp"
#include <map>

namespace Wand
{

class GlyphController
{
	protected:
	std::map<HexIndex,GlyphGraphicalObject> m_mapGlyph;

	public:
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
};

typedef Wand::GlyphController TheGlyphController;

#endif
