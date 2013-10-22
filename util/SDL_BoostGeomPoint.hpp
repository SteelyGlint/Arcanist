
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

#include <SDL.h>

namespace bg=boost::geometry;

BOOST_GEOMETRY_REGISTER_POINT_2D(SDL_Point, int, cs::cartesian, x, y) 

struct SDL_BBox
{
	SDL_Point ll;
	SDL_Point ur;

	operator SDL_Rect();
	SDL_BBox(SDL_Rect const& rhs);
};

BOOST_GEOMETRY_REGISTER_BOX(SDL_BBox, SDL_Point, ll, ur);

SDL_BBox::operator SDL_Rect()
{
	int x{bg::get<bg::min_corner,0>(*this)};
	int y{bg::get<bg::min_corner,1>(*this)};

	SDL_Rect ret{x,y,
		bg::get<bg::max_corner,0>(*this) - x,
		bg::get<bg::max_corner,1>(*this) - y};

return ret;
}


SDL_BBox::SDL_BBox(SDL_Rect const& rhs)
: ll{rhs.x,rhs.y}, ur{rhs.x+rhs.w,rhs.y+rhs.h} { }
	
	

/*
namespace boost { namespace geometry { namespace traits {

template <typename C, std::size_t D, typename S>
struct tag< myPoint<C, D, S> >
{
    typedef point_tag type;
};
template <typename C, std::size_t D, typename S>
struct coordinate_type< myPoint<C, D, S> >
{
    typedef C type;
};
template <typename C, std::size_t D, typename S>
struct coordinate_system< myPoint<C, D, S> >
{
    typedef S type;
};
template <typename C, std::size_t D, typename S>
struct dimension< myPoint<C, D, S> >
{
    static const std::size_t value = D;
};
template <typename C, std::size_t D, typename S, std::size_t I>
struct access<myPoint<C, D, S>, I>
{
    static inline C get(myPoint<C, D, S> const& p)
    {
        return p.template get<I>();
    }

    static inline void set(myPoint<C, D, S> & p, C const& v)
    {
        p.template set<I>(v);
    }
};
*/
