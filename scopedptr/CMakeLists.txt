cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(StringProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -fsanitize=address")

# Add the executable
add_executable(main main.cpp)
