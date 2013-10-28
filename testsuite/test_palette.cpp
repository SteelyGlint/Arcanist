#include <iostream>
#include "DynamicPalette.hpp"

template<int N,int DELAY = 400,int DELTA=65>
void screen_color_test(SDL_Renderer *rend)
{
	constexpr SDL_Color test = baseColors[N];
	constexpr MoteColor start_color = MoteColor::FromSDLColor(test);

	constexpr MoteColor testa[] = { 
		start_color.darken(DELTA*2),
		start_color.darken(DELTA), 
		start_color, 
		start_color.brighten(DELTA), 
		start_color.brighten(DELTA*2) 
	};

	int i;
	for(i = 0; i < sizeof(testa)/sizeof(MoteColor);++i)
	{

		SDL_SetRenderDrawColor(rend, testa[i].r, testa[i].g, testa[i].b, testa[i].a);  
		SDL_RenderClear(rend);
		SDL_RenderPresent(rend);
		SDL_Delay(DELAY);
	}

}

extern void test_main(SDL_Window *, SDL_Renderer *);

int main()
{
	SDL_Window *win;
	SDL_Renderer *rend;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 0;

	win = SDL_CreateWindow("Chapter 1:Setting up SDL",
		SDL_WINDOWPOS_CENTERED,  
		SDL_WINDOWPOS_CENTERED,  
		800, 600, 
		SDL_WINDOW_SHOWN);

	if( win == 0 )
		return 0;

	rend = SDL_CreateRenderer(win, -1, 0);

	if(rend == 0)
		return 0;


	test_main(win,rend);
	SDL_Quit();

	return 1;
}


#if 0 
/*SDL_Palette *tempPalette = 
	SDL_AllocPalette(5);

//SDL_FreePalette(tempPalette);


SDL_SetPaletteColors(surface, colors, first_color, num_colors)


	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);  

	/* Fill colors with color information */
	for(i=0;i<256;i++){
	  colors[i].r=i;
	  colors[i].g=i;
	  colors[i].b=i;
	}

	/* Set palette */
	SDL_SetPaletteColors(screen, colors, 0, 256);
}

#endif


