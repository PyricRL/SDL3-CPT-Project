#include "SDL3/SDL.h"

#include "dataHandler.hpp"

#include <iostream>

static SDL_Window* window;
static SDL_Renderer* renderer;

/**
 * For setting up CMake:
 * git clone https://github.com/libsdl-org/SDL.git include/SDL
 * create main.c/cpp file
 * create CMakeLists.txt file
 * mkdir build
 * cd build
 * cmake ..
 * cmake --build .
 * ./<exe-name>
 */

/**
 * For buttons at bottom:
 * need cmake tools extension
 * ctrl + shift + p
 * >CMake: Configure
 * >CMake: Build
 * >CMake: Run Without Debugging
 * >CMake: Debug
 */

 /**
  * Fix to bug showing commit to the vendored/SDL folder:
  * git submodule deinit -f vendored/SDL
  * git rm -rf --cached vendored/SDL
  * rm -rf .git/modules/vendored/SDL
  */

void update(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}

	if (!SDL_CreateWindowAndRenderer("Hello SDL!", 800, 600, 0, &window, &renderer)) {
		SDL_Log("SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
		return 1;
	}

	if (generateData(10, "Merge"))
	{
		std::cout << "GenerateData failed with error" << std::endl;
		return 1;
	}

	std::vector<int> array(10);

	if (displayDataToScreen(array, 10, renderer, window)) {
		std::cout << "DisplayDataToScreen failed with error" << std::endl;
		return 1;
	}

    bool running = true;

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

        update(renderer);
    }
}