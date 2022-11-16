#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"

int main(int argc, char* argv[])
{
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Triviador", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 40, 70, 180, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(10000);

	SDL_Quit();

	return 0;
}