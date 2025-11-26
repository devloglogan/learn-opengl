#include <cstdlib>
#include <iostream>

#include "SDL3/SDL.h"
#include "glad/glad.h"

int main() {
	SDL_Window *window;
	bool done = false;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Learn OpenGL", 640, 480, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		std::cerr << "Failed to create context: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
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

	exit(EXIT_SUCCESS);
}
