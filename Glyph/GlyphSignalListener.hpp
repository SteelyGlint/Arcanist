#ifndef __GlyphSignalListener_hpp__
#define __GlyphSignalListener_hpp__

namespace Wand {
namespace Glyph {


template<template <typename> class Derived>
class SignalListener : public Derived<SignalListener>
{
	typedef Derived<SignalListener> Base;
public:
	void onSignalReceived() { }
};

}/* Glyph */
}/* Wand */


#endif
