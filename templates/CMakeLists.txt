cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(StringProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-DEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -fsanitize=address")

# Add the executable
add_executable(array array.cpp)
add_executable(inheritance inheritance.cpp)
add_executable(copy copy.cpp)
add_executable(specialization specialization.cpp)
add_executable(array_size array_size.cpp)
