cmake_minimum_required(VERSION 3.5.0)
project(csvParser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(csvParser
    "CSVParser.h"
    "CSVParser.cpp"
    "main.cpp"
)

