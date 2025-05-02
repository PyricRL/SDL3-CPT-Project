#include <iostream>
#include <vector>

// Parse header for the input
#include "Parse.hpp"

// All the sort algorithm functions
#include "bubble.hpp"
#include "insertion.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "selection.hpp"

// Simple method that prints all items from an array
void printArray(const std::vector<int> data);

int runBack()
{
    ArrayConfigs data = parseCSV("../../../data/programIn.csv");

    if(data.type == "b") {
        bubble(data.array);
        return 0;
    }

    if(data.type == "i") {
        insertion(data.array);
        printArray(data.array);
        return 0;
    }

    if(data.type == "m") {
        return 1;
    }

    if(data.type == "q") {
        return 1;
    }

    if(data.type == "s") {
        return 1;
    }

    return 0; 
}

void printArray(const std::vector<int> data)
{
    for(int i=0;i<data.size();i++)
    {
        std::cout << data.at(i) << ", ";
    }
    std::cout << std::endl;
}