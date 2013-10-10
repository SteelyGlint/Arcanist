#ifndef __SignalManager_hpp__
#define __SignalManager_hpp__
#include <queue>
#include <string>
#include <functional>

class GlyphBase;

class SignalDirected
{
public:
	bool operator<(SignalDirected const &rhs) const
	{
		return m_arrival_tick < rhs.m_arrival_tick;
	}

private:
	int m_arrival_tick; //= std::integral_max_int;

	GlyphBase *m_src = nullptr;
	GlyphBase *m_dest = nullptr;

	//std::string m_message;
	//std::function<void(BaseGlyph::*)(BaseGlyph*,std::string)> m_func;
};


class SignalManager
{
public:
	bool init();
	void update();
	void draw();
	void clean();

	bool manageSignal(SignalDirected const & m_msg)
	{
		m_gameMessages.push(m_msg);
		return true;
	}

	static SignalManager *Instance()
	{
		if(p_sInstance == 0)
			p_sInstance = new SignalManager();

		return p_sInstance;
	}
private:
	std::priority_queue<SignalDirected> m_gameMessages;

	SignalManager() = default;
	~SignalManager() = default;
	static SignalManager* p_sInstance;
};

typedef SignalManager TheSignalManager;


#endif
