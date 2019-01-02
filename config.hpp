#pragma once
#include <algorithm>
#include <SDL2/SDL.h>

using namespace std;

extern void plot(int arr[]);
extern SDL_Renderer * renderer;
extern SDL_Event event;

int input() {
	while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							return 1;
					}
			}
	}
	return -1;
}

void start(int arr[]) {
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(renderer);
		plot(arr);
		SDL_RenderPresent(renderer);
}

void swap_pos(int arr[], int &a, int &b) {
	start(arr);
	swap(a, b);
}

