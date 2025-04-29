#include "dataHandler.hpp"

#include "../backend/cpp/run.hpp"

static std::vector<std::vector<std::string>> temp;

int generateData(int length, std::string Type) {
    std::vector<std::string> headerStr; // Vector of headers
    std::vector<std::string> dataStr;   // Vector of data
    std::vector<int> indices(length);   // Vector to hold indices 0 to length-1
    std::iota(indices.begin(), indices.end(), 0); // Fill with 0, 1, 2, ..., length-1

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the indices randomly
    std::shuffle(indices.begin(), indices.end(), gen);

    std::stringstream lengthStr;
    lengthStr << length;

    headerStr.push_back("Length"); // Add "Length" as a string
    dataStr.push_back(lengthStr.str());

    for (int j = 0; j < length; j++) {
        int i = indices[j]; // Get the randomized index
        std::stringstream arrayIdx;
        std::stringstream arrayInt;
        arrayIdx << "A" << i;
        arrayInt << i + 1;
        headerStr.push_back(arrayIdx.str()); // Add the string from stringstream
        dataStr.push_back(arrayInt.str());   // Add the int from stringstream
    }

    headerStr.push_back("Type"); // Add "Type" as a string
    dataStr.push_back(Type);

    temp.push_back(headerStr);
    temp.push_back(dataStr);

    // open file to write to
    std::ofstream outputFile("../../data/programIn.csv");

    if (!outputFile.is_open())
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return 1;
    }

    // Check for first index of array (length)
    // Note: The element at temp[0][1] will now correspond to the *first* randomized index.
    // If you intended to always access the *first* generated array element, regardless of randomization,
    // you might need to adjust how you access it.
    if (!temp[0].empty() && temp[0].size() > 1) {
        std::string secondRowFirstColumn = temp[0][1];
        std::cout << "0, 1: " << secondRowFirstColumn << std::endl;
    } else {
        std::cerr << "Error: temp[0] does not have at least two elements." << std::endl;
    }

    // write the temp vector to the file
    for (const auto& row : temp)
    { // Iterate through each row in temp
        for (size_t i = 0; i < row.size(); ++i)
        { // Iterate through each element in the row
            outputFile << row[i];
            if (i < row.size() - 1)
            {
                outputFile << ","; // Add comma separator
            }
        }
        outputFile << std::endl; // Add newline for the next row
    }

    outputFile.close();
    return 0;
}

int displayDataToScreen(SDL_Renderer* renderer, SDL_Window* window) {
    /**
     * Here needs to parse the data and then display it
     * Maybe we have an input box somewhere on the screen which takes input and calls
     * GenerateData() with the arguments
     * I have something written in c but that doesn't transfer over...
     * imma let you deal with this lol
     */

    int pythonResult = system("python ../../src/backend/python/parseData.py ../../data/programIn.csv ../../data/pythonOut.csv");
    if (pythonResult == 0) {
        std::cout << "Python script executed successfully." << std::endl;
    } else {
        std::cerr << "Error executing Python script." << std::endl;
    }

    int cppResult = runBack();
    if (cppResult == 0) {
        std::cout << "C++ script executed successfully." << std::endl;
    } else {
        std::cerr << "Error executing C++ script." << std::endl;
    }

    ArrayConfigs data = parseCSV("../../data/programIn.csv");

    auto max_it = std::max_element(data.array.begin(), data.array.end());
    int scaleFactor = *max_it;
    
    /**
    * from here, plan is to get bounds of full window and allow for buttons on the bottom, 
    * as well as 2 different surfaces which contain the sorts
    */
    
    SDL_Surface* cppSortSurface = SDL_CreateSurface(200, 400, SDL_PIXELFORMAT_UNKNOWN);
    
    for (int i = 0; i < data.size - 1; i++) {
        SDL_FRect rect;
        rect.x = i + 5;
        rect.y = 0;
        rect.w = i + 5;
        rect.h = i;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    SDL_RenderFillRect(renderer, &rect);
    }
    return 0;
}