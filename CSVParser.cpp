#include "CSVParser.h"

CSVParser::CSVParser(const std::string &filename, char delimiter = ',')
    : filename(filename), delimiter(delimiter), expected_columns(0)
{
    if (delimiter != ',' && delimiter != '\t')
        throw std::invalid_argument("Invalid delimiter. Use ',' or '\\t'");
}

dataframe CSVParser::parse()
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    dataframe data;
    std::string line;
    size_t line_number = 0;

    if (std::getline(file, line))
    {
        ++line_number;
        data.first = splitString(line);
        expected_columns = data.first.size();
    }

    while (std::getline(file, line))
    {
        ++line_number;
        std::vector<double> double_row = splitDouble(line, line_number);
        if (double_row.size() != expected_columns)
            throw std::runtime_error("Row " + std::to_string(line_number) +
                                     " has an inconsistent number of columns. Expected " +
                                     std::to_string(expected_columns) + " but got " +
                                     std::to_string(double_row.size()));
        data.second.push_back(double_row);
    }

    if (file.bad())
        throw std::runtime_error("Error reading file: " + filename);

    return data;
}

std::vector<std::string> CSVParser::splitString(const std::string &line)
{
    std::vector<std::string> tokens;
    std::istringstream lineStream(line);
    std::string token;

    while (std::getline(lineStream, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

bool CSVParser::isDouble(const std::string &str)
{
    std::istringstream iss(str);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}

std::vector<double> CSVParser::splitDouble(const std::string &line, size_t line_number)
{
    std::vector<double> tokens;
    std::istringstream lineStream(line);
    std::string token;
    size_t column_number = 0;

    while (std::getline(lineStream, token, delimiter))
    {
        if (!isDouble(token))
            throw std::runtime_error("Invalid number format in row " + std::to_string(line_number) +
                                     ", column " + std::to_string(column_number) + ": " + token);
        std::istringstream(token) >> tokens.emplace_back();
        ++column_number;
    }

    return tokens;
}