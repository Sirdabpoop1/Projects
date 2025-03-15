cmake_minimum_required(VERSION 3.13)

project(HiLoGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES game.cpp utils.cpp)

# Add executable
add_executable(HiLoGame ${SOURCE_FILES})
