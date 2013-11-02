#ifndef __HexDim_hpp__
#define __HexDim_hpp__

#include <cmath>
#include <complex>

#include <boost/geometry/geometries/point_xy.hpp>

namespace bgm=boost::geometry::model;


namespace wand {
namespace hex {

struct hex_shape_flat_tag {};
struct hex_shape_pointy_tag {};

template<typename S>
struct PolygonSides;
/*
{
	static_assert(false,"invalid hex shape specialization");
};
*/
template<>
struct PolygonSides<hex_shape_flat_tag>
{
	enum HexSide { NORTHWEST, NORTH, NORTHEAST, SOUTHEAST, SOUTH, SOUTHWEST };
	typedef hex_shape_flat_tag type;
};

template<>
struct PolygonSides<hex_shape_pointy_tag>
{
	enum HexSide { WEST, NORTHWEST, NORTHEAST, EAST, SOUTHEAST, SOUTHWEST, };
	typedef hex_shape_pointy_tag type;
};



namespace detail {

constexpr float rnd(float x);
constexpr bool same(float lhs, float rhs);



static constexpr float FLT_PREC = 0.0001f;
static constexpr float SQRT_3 = 1.732051f;

}


class HexagonDim
{
	const float m_Radius;
	const float m_Width;
	const float m_Height;
	const float m_Side;

protected:
	static constexpr float FLT_PREC = detail::FLT_PREC;
	static constexpr float SQRT_3 = detail::SQRT_3;

public:

	constexpr HexagonDim(const float &r) :
		 m_Radius(detail::rnd(r)), 
		 m_Width(detail::rnd(r*2.f)), 
		 m_Height(detail::rnd(HexagonDim::SQRT_3*r)), 
		 m_Side(detail::rnd((r*3.f)/2.f))
	{

	}

	constexpr float HalfHeight() const { return detail::rnd(m_Height/2.f); }
	constexpr float Radius() const { return m_Radius; }
	constexpr float Width() const { return m_Width; }
	constexpr float Height() const { return m_Height; }
	constexpr float Side() const { return m_Side; }


	friend inline constexpr float detail::rnd(float x);
	friend inline constexpr bool detail::same(float lhs, float rhs);
};




namespace detail {
inline constexpr float rnd(float x)
{
	return std::floor(0.5f + (x/HexagonDim::FLT_PREC))*HexagonDim::FLT_PREC;
}


inline constexpr bool same(float lhs, float rhs)
{
	return std::fabs(lhs) < std::fabs(rhs) ?
		(std::fabs(rhs) - std::fabs(lhs)) < HexagonDim::FLT_PREC :
		(std::fabs(lhs) - std::fabs(rhs)) < HexagonDim::FLT_PREC;
}

inline constexpr float abs_f(float x)
{
	return { x < 0.f ? -x : x};
}
}

} /* Hex */
} /* Wand */


#endif
