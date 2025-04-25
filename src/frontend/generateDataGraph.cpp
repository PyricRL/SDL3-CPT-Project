#include "generateDataGraph.hpp"

int displayDataToScreen(std::vector<int> array, int length, SDL_Renderer* renderer, SDL_Window* window) {
    for (int i = 0; i < length - 1; i++) {
        std::cout << array[i] << std::endl;
    }
    return 0;
}