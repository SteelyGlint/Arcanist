#ifndef __MoteMovementManager_hpp__
#define __MoteMovementManager_hpp__
#include <vector>

class GameObject;

class MoteMovementManager
{
public:
	bool init();
	void update();
	void draw();
	void clean();

	template<typename T>
	bool manageMote(T* m_obj)
	{
		m_gameObjects.push_back(m_obj);
		return true;
	}

	static MoteMovementManager *Instance()
	{
		if(p_sInstance == 0)
			p_sInstance = new MoteMovementManager();

		return p_sInstance;
	}
private:
	std::vector<GameObject *> m_gameObjects;

/* copy of Hex and HexGrid dim */
	HexIndex hexgrid_dim;
	HexIndex hex_dim;

	MoteMovementManager() = default;
	static MoteMovementManager* p_sInstance;
};

typedef MoteMovementManager TheMoteMovementManager;


#endif
