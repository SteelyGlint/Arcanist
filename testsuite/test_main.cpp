#include <iostream>
#include <SDL.h>

void test_main(SDL_Window *, SDL_Renderer *);

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


