#include "CSVParser.hpp"
#include "../backend/cpp/run.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

CSVParser::CSVParser(const std::string& filePath, bool hasHeader, char delimiter)
    : m_filePath(filePath), m_delimiter(delimiter), m_hasHeader(hasHeader) {}

int CSVParser::parse() {
    std::ifstream file(m_filePath);

    if (!file) {
        std::cerr << "Cannot open file for parsing" << std::endl;
        return 1;
    }

    std::vector<std::vector<std::string>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " "; // Use tab for better formatting
        }
        std::cout << std::endl; // Move to the next line after printing all cells in a row
    }

    std::cout << data[1][10] << std::endl;
    
    return 0;
}

std::vector<std::string> CSVParser::getHeader() const {
    return m_header;
}

std::vector<std::vector<std::string>> CSVParser::getDataWithoutHeader() const {
    return m_dataWithoutHeader;
}