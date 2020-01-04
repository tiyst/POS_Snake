#cmake_minimum_required(VERSION 3.15)
#project(Snakerino)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic ")
#set(SOURCE_FILES main.cpp)
#
#find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
#
#add_executable(Snakerino ${SOURCE_FILES})
#target_link_libraries(Snakerino sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

#cmake_minimum_required(VERSION 3.15)
#project(Snakerino)
#
#set(CMAKE_CXX_STANDARD 14)
#
##set(SFML_INCLUDE_DIR "./sfml/include/SFML")
#set(SFML_LIBRARY_DIR "./sfml/lib")
#set(SFML_DIR "./sfml/lib/cmake/SFML")
#
##include_directories(SFML_INCLUDE_DIR)
#link_directories(SFML_LIBRARY_DIR)
#
##TODO fails here (Google)
#find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
#
#include_directories(${SFML_INCLUDE_DIRS})
#if(SFML_FOUND)
#    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
#    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
#endif()
#
#add_executable(Snakerino main.cpp)
#target_link_libraries (Snakerino sfml-graphics sfml-window sfml-system sfml-audio sfml-network)


#cmake_minimum_required(VERSION 3.15)
#project(Snakerino)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#
#set(SOURCE_FILES main.cpp)
#add_executable(Snakerino ${SOURCE_FILES})
#include_directories(/include)
#
#find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
#include_directories(${SFML_INCLUDE_DIRS})
#target_link_libraries(Snakerino sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

cmake_minimum_required(VERSION 3.15)

project(Snakerino)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

#TODO repair cmake include errors
#set(SFML_DIR "./sfml/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(Snakerino main.cpp)
target_link_libraries(Snakerino sfml-system sfml-window sfml-graphics sfml-audio sfml-network)