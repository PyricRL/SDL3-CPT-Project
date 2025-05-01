#pragma once

#include <string>
#include <vector>

class CSVParser {
public:
    CSVParser(const std::string& filePath, bool hasHeader, char delimiter = ',');

    int parse();
    std::vector<std::string> getHeader() const;
    std::vector<std::vector<std::string>> getDataWithoutHeader() const;
private:
    std::string m_filePath;
    char m_delimiter;
    bool m_hasHeader;
    std::vector<std::string> m_header;
    std::vector<std::vector<std::string>> m_dataWithoutHeader;
};