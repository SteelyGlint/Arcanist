#ifndef __SDLGameObject_hpp__
#define __SDLGameObject_hpp__

#include <string>
#include "GameObject.hpp"


class SDLGameObject : public GameObject
{
public:
	SDLGameObject(LoaderParams const& pParams);

	virtual void draw();
	virtual void update() {}
	virtual void clean() {}

protected:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	int m_startTick;

};

#endif
