cmake_minimum_required(VERSION 3.1)

project(KDTree VERSION 1.0
  DESCRIPTION "Lightweight C++ KDTree Implementation"
LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-g")

add_library(KDTree KDTree.hpp KDTree.cpp Node.cpp)

# Supply build directives here by uncommenting and changing 'driver.cpp'
# to the name of your own implementation

# add_executable(${CMAKE_PROJECT_NAME} driver.cpp)
# target_link_libraries(${CMAKE_PROJECT_NAME} kdtree)
