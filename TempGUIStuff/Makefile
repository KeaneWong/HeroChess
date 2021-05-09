# Makefile (RD, 1/17/13)

all: SDL_DisplayBitmap SDL_DisplayBitmap2 SDL_DisplaySmiley

clean:
	rm -f SDL_DisplayBitmap SDL_DisplayBitmap2 SDL_DisplaySmiley

SDL_DisplayBitmap: SDL_DisplayBitmap.c
	gcc SDL_DisplayBitmap.c -o SDL_DisplayBitmap -Wall -lSDL

SDL_DisplayBitmap2: SDL_DisplayBitmap2.c
	gcc SDL_DisplayBitmap2.c -o SDL_DisplayBitmap2 -Wall -lSDL

SDL_DisplaySmiley: SDL_DisplaySmiley.c
	gcc SDL_DisplaySmiley.c -o SDL_DisplaySmiley -Wall -lSDL

