#ifndef __GlyphMoteListener_hpp__
#define __GlyphMoteListener_hpp__

#include <deque>

namespace Wand {
namespace Glyph {

template<template <typename> class Derived>
class MoteListener : public Derived<MoteListener>
{
	typedef Derived<MoteListener> Base;
public:
template<typename MOTE>
void onMoteEntered(MOTE &m)
{
	Base::onMoteEntered(m);
}

template<typename MOTE>
bool onMoteEnteredAccept(MOTE &m)
{
	if(Base::onMoteEnteredAccept(m))
	{
		onMoteEntered(m);
		return true;
	}
	return false;
}

};

}/* Glyph */
}/* Wand */


#endif
