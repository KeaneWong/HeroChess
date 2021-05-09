// 05/06/21  Irania M. Started GUI

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{

	//We must first initialize the SDL video component, and check for success
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Window* win = SDL_CreateWindow("Hero Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if (!win)
	{
		printf("Unable to create window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;	
	}
	
	// create renderer which sets up the graphics hardware	 
	Unit32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	if (!rend)
	{
		printf("Unable to create render: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	// loads image into memory 
	SDL_Surface* suface = IMG_Load("[image name]");
	if (!surface)
	{
		printf("Unable to create surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	// load image to graphics hardware's memory
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex)
	{
		prtinf("Unable to create texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	// struct to hold position and size of sprite
	SDL_Rect dest;	


}
  
//  EOF //
