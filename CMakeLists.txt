cmake_minimum_required(VERSION 3.15)
project(POS_Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic ")
set(SOURCE_FILES main.cpp)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(POS_Snake ${SOURCE_FILES})
target_link_libraries(POS_Snake sfml-graphics sfml-window sfml-system )