#include <iostream>
#include <SDL.h>
#include "HexGrid.hpp"
#include "MoteGraphicalObject.hpp"
#include "MoteMovementManager.hpp"
#include "Glyph.hpp"
#include "GlyphController.hpp"


namespace Wand {
MoteMovementManager * MoteMovementManager::p_sInstance = NULL;

bool MoteMovementManager::init()
{
	return true;
}

void MoteMovementManager::update()
{
	for( auto &obj : m_gameObjects )
	{
		obj->update();
		MoteGraphicalObject *mObj;

		if( (mObj = dynamic_cast<MoteGraphicalObject *>(obj)) != NULL)
		{
			if(mObj->x() < 0)
				mObj->setBearing(Bearing::E);

			else if(mObj->x()+9 >= 680)
				mObj->setBearing(Bearing::W);
		}
	}
}

void MoteMovementManager::draw()
{
	for( auto &obj : m_gameObjects )
	{
		obj->draw();
	}
}


void MoteMovementManager::clean()
{
}

} /* namespace wand */


#if 0
	if( int(((SDL_GetTicks() / 100) % 50)) )
	{
		MoteGraphicalObject* m_partTest = new MoteGraphicalObject(LoaderParams{m_x,m_y,9,9,"greyscale"});

		m_partTest->setBearing(Bearing::E);
		TheMoteMovementManager::Instance()->manageMote(m_partTest);
	}

#endif
