#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "dataHandler.hpp"
#include "CSVParser.hpp"

#include <iostream>

static SDL_Window* window;
static SDL_Renderer* renderer;
static TTF_Font* font;
static SDL_Surface* screenSurface;

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
  * git rm -rf .git/modules/vendored/SDL
  */

int renderText(SDL_Renderer* renderer, float fontSize, std::string text, int x, int y, std::string flags) {
	font = TTF_OpenFont("../../Roboto-VariableFont_wdth,wght.ttf", fontSize);
	if (!font) {
		SDL_Log("Font Initialize Error: %s", SDL_GetError());
		return 1;
	}

	SDL_Color color = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
	
	if (!surface) {
		SDL_Log("TTF_RenderText_Solid Error: %s", SDL_GetError());
		return 1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		return 1;
	}

	SDL_FRect dst;

	// If the flag is "center", then it takes the coords given and uses them as the center for the text,
	// rather than the top left
	if (flags == "center") {
		dst = { (float)(x - (surface->w/2)), (float)(y - (surface->h / 2)), (float)surface->w, (float)surface->h};
	}
	else {
		dst = { (float)x, (float)y, (float)surface->w, (float)surface->h };
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderTexture(renderer, texture, nullptr, &dst);

	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
	return 0;
}

int main(int argc, char* argv[]) {
	if (!TTF_Init()) {
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}

	if (!SDL_CreateWindowAndRenderer("Hello SDL!", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &window, &renderer)) {
		SDL_Log("SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
		return 1;
	}

	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

	if (!screenSurface) {
		SDL_Log("SDL_GetWindowSurface Error: %s", SDL_GetError());
		return 1;
	}

	// if (generateData(10, "bubble"))
	// {
	// 	std::cout << "GenerateData failed with error" << std::endl;
	// 	return 1;
	// }
	
	// if (pullDataFromFunctions()) {
	// 	std::cout << "PullDataFromFunctions failed with error" << std::endl;
	// 	return 1;
	// }

	std::vector<int> array(10);

    bool running = true;

	SDL_Event event;

	std::string filepath = "../../data/pythonOut.csv";

	CSVParser parser(filepath, true, ',');

	parser.parse();

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		renderText(renderer, 50, "Hello, World!", screenSurface->w / 2, 100, "center");
		displayDataToScreen(renderer, window, screenSurface, 0, 0, 9999, 9999, 2);
		SDL_RenderPresent(renderer);
    }
}