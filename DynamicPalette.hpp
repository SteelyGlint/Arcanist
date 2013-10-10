#ifndef __DynamicPalette_hpp__
#define __DynamicPalette_hpp__
#include <SDL.h>

enum class Element { Void, Chaos, Fire, Spark, Life, Flow };


constexpr SDL_Color baseColors[] = {
	SDL_Color{0,0,255},		/* Void */
	SDL_Color{255,0,255},   /* Chaos */
	SDL_Color{255,0,0},		/* Fire */
	SDL_Color{255,255,0},   /* Spark */
	SDL_Color{0,255,0},     /* Life */
	SDL_Color{0,255,255}    /* Flow */
};

enum class Color { RED, GREEN, BLUE, ALPHA };

struct MoteColor
{
	Uint8 r,g,b,a;
	
	static constexpr MoteColor FromSDLColor(SDL_Color const &c)
	{
		return {c.r, c.g, c.b, 255};
	}

	constexpr MoteColor darken(Uint8 d)
	{ 
		return { 
			(Uint8) (r <= d ? 0 : r - d),
			(Uint8) (g <= d ? 0 : g - d),
			(Uint8) (b <= d ? 0 : b - d), 
			a };
	}

	constexpr MoteColor brighten(Uint8 d)
	{ 
		return { 
			(Uint8) (((int) r + (int)d >= 255) ? 255 : r + d),
			(Uint8) (((int) g + (int)d >= 255) ? 255 : g + d),
			(Uint8) (((int) b + (int)d >= 255) ? 255 : b + d),
			a };
	}

	constexpr MoteColor brighten(Color c, Uint8 d)
	{ 
		return { 
			(c == Color::RED   ? (Uint8) (((int) r + (int)d >= 255) ? 255 : r + d) : r),
			(c == Color::GREEN ? (Uint8) (((int) g + (int)d >= 255) ? 255 : g + d) : g),
			(c == Color::BLUE  ? (Uint8) (((int) b + (int)d >= 255) ? 255 : b + d) : b),
			(c == Color::ALPHA ? (Uint8) (((int) a + (int)d >= 255) ? 255 : a + d) : a),
			};
	}

	constexpr MoteColor darken(Color c, Uint8 d)
	{ 
		return { 
		(c == Color::RED     ?	(Uint8) (r <= d ? 0 : r - d) : r),
		(c == Color::GREEN   ? 	(Uint8) (g <= d ? 0 : g - d) : g),
		(c == Color::BLUE    ? 	(Uint8) (b <= d ? 0 : b - d) : b), 
		(c == Color::ALPHA   ? 	(Uint8) (a <= d ? 0 : a - d) : a)
		};
	}

	
};

#endif
