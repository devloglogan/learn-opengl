#include <stdio.h>

#include "SDL3/SDL.h"
#include "glad/glad.h"

int main() {
	SDL_Window *window;
	bool done = false;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Learn OpenGL", 640, 480, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		fprintf(stderr, "Failed to create context: %s\n", SDL_GetError());
		return 1;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		return 1;
	}

	while (!done) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
