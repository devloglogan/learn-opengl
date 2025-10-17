#include <cstdlib>

#include "SDL3/SDL.h"

int main() {
	SDL_Window *window;
	bool done = false;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Learn OpenGL", 640, 480, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	while (!done) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
		}

		// TODO: Render logic
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
