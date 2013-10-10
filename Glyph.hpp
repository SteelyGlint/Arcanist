#ifndef __Glyph_hpp__
#define __Glyph_hpp__
#include "HexGrid.hpp"
#include "SDLGameObject.hpp"



namespace Glyph
{


enum class Glyph_Type { Signal, Counter, Extract, Transport, Sort, Pluck, Insert, Storage, Engine, Split, Furnace, Purify, Diffusion, Sensor, Analysis, Assembly, Reactor_Core, Reactor_Perim, Conduit };

class GlyphBase
{

public: /* private: after GlyphBuilder class */
	GlyphBase(Glyph_Type p_gtype, HexIndex p_hid)
		: m_glyph_type(p_gtype), m_loc(p_hid)
	{
	}

public:
	Glyph_Type	m_glyph_type;
	HexIndex		m_loc{2,2};
};



class GlyphGraphicalObject : public SDLGameObject
{
public:
	GlyphGraphicalObject(LoaderParams const& pParams)
		: SDLGameObject(pParams),
			m_glyphData(Glyph_Type::Extract, 
				TheHexGrid::Instance()->atPoint(m_x,m_y)) { }


	virtual void draw();
	virtual void update();
	//virtual void clean();

	GlyphBase const &data() { return m_glyphData; }

private:
	GlyphBase m_glyphData;


};

};

#endif
