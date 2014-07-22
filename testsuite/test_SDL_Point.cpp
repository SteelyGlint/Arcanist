#include <util/SDL_BoostGeomPoint.hpp>

#include <cstdint>
#include <tuple>
#include <utility>
#include <vector>

#include <stdexcept>
#include <iostream>



namespace bg=boost::geometry;

struct constPoint
{
	const SDL_Point * const p;
	std::size_t sz;

	template<std::size_t N>
	constexpr constPoint(const SDL_Point (&a)[N] ) : p(a), sz(N) {}
	std::size_t size() const { return sz; }

	constexpr SDL_Point operator[](std::size_t n) const 
	{ return n < sz ? p[n] : throw std::out_of_range(""); }
};


int main(int argc, char *argv[])
{
	static constexpr SDL_Point a_pts[] = {{0,0},{1,1}};
	static constexpr constPoint constArray(a_pts);

	static_assert(constArray.size() == 2,"Array was not initialized properly");


	std::cout << bg::dsv(constArray[0]);
	std::cout << bg::dsv(constArray[1]);

}
