#include "Parse.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

ArrayConfigs parseCSV(std::string fileName)
{
    std::ifstream file(fileName);

    // Variables to generate config
    int size;
    std::vector<int> data;
    std::string type;

    std::string line;
    
    // Read from file
    while(getline(file, line))
    {
        if(line[0] != 'L')
        {
            std::stringstream buffer;

            int i=0;

            while(line[i] != ',')
            {
                buffer << line[i];
                i++;
            }
        
            // Convert the buffer to a string and then into an integer
            buffer >> size;

            //Clear buffer for more use
            buffer.clear();

            // Counts how many times an element was extracted
            int counter = 0;
            while(counter < size)
            {
                while(line[++i] != ',')
                {
                    buffer << line[i];
                }

                // temporary variable to store the buffer data in then push back to
                // the data vector
                int temp;
                buffer >> temp;
                data.emplace_back(temp);

                buffer.clear();
                
                counter++;
            }

            type = line[++i];
        }
    }

    ArrayConfigs newConfig = {size, type, data};
    return newConfig;
}