#include "CSVParser.h"
#include <iomanip>

void printDataframe(const dataframe &data)
{
    std::vector<size_t> column_widths(data.first.size(), 0);

    for (size_t i = 0; i < data.first.size(); ++i)
        column_widths[i] = std::max(column_widths[i], data.first[i].size());

    for (const auto &row : data.second)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << row[i];
            column_widths[i] = std::max(column_widths[i], oss.str().size());
        }
    }

    for (size_t i = 0; i < data.first.size(); ++i)
        std::cout << std::setw(column_widths[i]) << data.first[i] << " ";
    std::cout << std::endl;

    for (const auto &row : data.second)
    {
        for (size_t i = 0; i < row.size(); ++i)
            std::cout << std::setw(column_widths[i]) << std::fixed << std::setprecision(2) << row[i] << " ";
        std::cout << std::endl;
    }
}

void tryCatchBlock(const std::string &filename, char delimiter)
{
    try
    {
        CSVParser parser(filename, delimiter);
        dataframe data = parser.parse();
        printDataframe(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main()
{
    tryCatchBlock("C:\\University\\C++\\csvParser\\dataTab.csv", '\t');
    tryCatchBlock("C:\\University\\C++\\csvParser\\test.csv", ',');
    tryCatchBlock("C:\\University\\C++\\csvParser\\testError1.csv", ',');
    tryCatchBlock("C:\\University\\C++\\csvParser\\testError2.csv", ',');
    tryCatchBlock("C:\\University\\C++\\csvParser\\testError3.csv", ',');
}
