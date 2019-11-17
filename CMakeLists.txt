cmake_minimum_required(VERSION 3.15)
project(Snakerino)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic ")
set(SOURCE_FILES main.cpp)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(Snakerino ${SOURCE_FILES})
target_link_libraries(Snakerino sfml-graphics sfml-window sfml-system sfml-audio sfml-network)