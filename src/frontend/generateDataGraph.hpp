#pragma once

#include <SDL3/SDL.h>
#include "../Backend/Cpp/Parse.hpp"

int displayDataToScreen(std::vector<int> array, int length, SDL_Renderer* renderer, SDL_Window* window);