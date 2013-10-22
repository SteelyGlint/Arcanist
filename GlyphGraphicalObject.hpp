#ifndef __GlyphGraphicalObject_hpp__
#define __GlyphGraphicalObject_hpp__
#include "SDLGameObject.hpp"

namespace Wand
{

class GlyphGraphicalObject : public SDLGameObject
{
public:
	GlyphGraphicalObject(LoaderParams const& pParams)
		: SDLGameObject(pParams)
	{ }


	virtual void draw();
	virtual void update();
	virtual void clean();

private:


};

};

#endif
