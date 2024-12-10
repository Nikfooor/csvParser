#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

typedef std::pair<std::vector<std::string>, std::vector<std::vector<double>>> dataframe;

class CSVParser
{
public:
    CSVParser(const std::string &filename, char delimiter);
    dataframe parse();

private:
    std::string filename;
    char delimiter;
    size_t expected_columns;

    std::vector<std::string> splitString(const std::string &line);
    std::vector<double> splitDouble(const std::string &line, size_t line_number);
    bool isDouble(const std::string &str);
};