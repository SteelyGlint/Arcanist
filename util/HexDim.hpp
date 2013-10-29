#ifndef __HexDim_hpp__
#define __HexDim_hpp__

#include <cmath>
#include <complex>

namespace wand {
namespace hex {

constexpr float rnd(float x);
constexpr bool same(float lhs, float rhs);


namespace detail {

constexpr float rnd(float x);
constexpr bool same(float lhs, float rhs);



class HexagonDim
{
	const float m_Radius;
	const float m_Width;
	const float m_Height;
	const float m_Side;

public:
	static constexpr float FLT_PREC = 0.0001f;
	static constexpr float SQRT_3 = 1.732051f;

	constexpr HexagonDim(const float &r) :
		 m_Radius(rnd(r)), m_Width(rnd(r*2.f)), m_Height(rnd(HexagonDim::SQRT_3*r)), m_Side(rnd((r*3.f)/2.f)) {}


	constexpr float HalfHeight() const { return rnd(m_Height/2.f); }
	constexpr float Radius() const { return m_Radius; }
	constexpr float Width() const { return m_Width; }
	constexpr float Height() const { return m_Height; }
	constexpr float Side() const { return m_Side; }
};


constexpr float rnd(float x)
{
	return std::floor(0.5f + (x/HexagonDim::FLT_PREC))*HexagonDim::FLT_PREC;
}


constexpr float abs_f(float x)
{
	return { x < 0.f ? -x : x};
}


} /* detail */

constexpr bool same(float lhs, float rhs)
{
	return std::fabs(lhs) < std::fabs(rhs) ?
		(std::fabs(rhs) - std::fabs(lhs)) < detail::HexagonDim::FLT_PREC :
		(std::fabs(lhs) - std::fabs(rhs)) < detail::HexagonDim::FLT_PREC;

}


//constexpr float SQRT_3 = 1.73205080757f;
//constexpr float R = 27.f;
//constexpr float W = R*2.f;
//constexpr float HALF_H = R*SQRT_3/2.f;
//constexpr float H = SQRT_3*R;
//constexpr float S = (R*3.f)/2.f;

} /* Hex */
} /* Wand */


#endif
