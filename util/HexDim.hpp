#ifndef __HexDim_hpp__
#define __HexDim_hpp__

#include <cmath>
#include <complex>

#include <boost/geometry/geometries/point_xy.hpp>

namespace bgm=boost::geometry::model;


namespace wand {
namespace hex {



namespace detail {

float rnd(float x);
bool same(float lhs, float rhs);

static float FLT_PREC = 0.0001f;
static float SQRT_3 = 1.732051f;

}


class HexagonDim
{
	float m_Radius;
	float m_Width;
	float m_Height;
	float m_Side;

public:
	HexagonDim(const float &r);

	float HalfHeight() const { return detail::rnd(m_Height/2.f); }
	float Radius() const { return m_Radius; }
	float Width() const { return m_Width; }
	float Height() const { return m_Height; }
	float Side() const { return m_Side; }


	friend inline float detail::rnd(float x);
	friend inline bool detail::same(float lhs, float rhs);
};

inline HexagonDim::HexagonDim(const float &r)
{
	m_Radius = detail::rnd(r);
	m_Width = detail::rnd(r*2.f);
	m_Height = detail::rnd(detail::SQRT_3*r);
	m_Side = detail::rnd((r*3.f) / 2.f);
}


namespace detail {
inline float rnd(float x)
{
	return std::floor(0.5f + (x/detail::FLT_PREC))*detail::FLT_PREC;
}


inline bool same(float lhs, float rhs)
{
	return std::fabs(lhs) < std::fabs(rhs) ?
		(std::fabs(rhs) - std::fabs(lhs)) < detail::FLT_PREC :
		(std::fabs(lhs) - std::fabs(rhs)) < detail::FLT_PREC;
}

inline float abs_f(float x)
{
	return { x < 0.f ? -x : x};
}
}

} /* Hex */
} /* Wand */


#endif
