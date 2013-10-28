#ifndef __GlyphMoteStorage_hpp__

#include <deque>

namespace Wand {
namespace Glyph {

template<typename Mote,
	template <typename ELEM, typename = std::allocator<ELEM> >
	class CONT = std::deque>
class MoteStorage : public CONT<Mote>
{
public:
};

}/* Glyph */
}/* Wand */


#endif
