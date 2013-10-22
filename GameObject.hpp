#ifndef __GameObject_hpp__
#define __GameObject_hpp__
#include <string>

namespace Wand
{

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID)
		: m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID) { }

	int x() const { return m_x; }
	int y() const { return m_y; }
	int width() const { return m_width; }
	int height() const { return m_height; }

	std::string textureID() const { return m_textureID; }

private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	std::string m_textureID;
};


class GameObject
{
public:
	virtual void draw()   = 0;
	virtual void update() = 0;
	virtual void clean()  = 0;

protected:

	GameObject(LoaderParams const & pParams) {}
	virtual ~GameObject() {}
};

};
#endif
