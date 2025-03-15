cmake_minimum_required(VERSION 3.13)

project(Megamind VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES game.cpp utils.cpp)

# Add executable
add_executable(Megamind ${SOURCE_FILES})