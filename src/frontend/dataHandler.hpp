#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>

#include <SDL3/SDL.h>

#include "../Backend/Cpp/Parse.hpp"

int generateData(int length, std::string Type);

int displayDataToScreen(std::vector<int> array, int length, SDL_Renderer* renderer, SDL_Window* window);