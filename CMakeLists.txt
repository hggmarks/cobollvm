cmake_minimum_required(VERSION 3.15)
project(cobollvm)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(cobollvm 
    src/cobollvm.cpp
    src/lexer.cpp
)
