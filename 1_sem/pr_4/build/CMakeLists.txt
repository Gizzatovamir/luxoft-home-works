cmake_minimum_required(VERSION 3.8)

project(Observer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Observer ../observer.cpp)

target_link_libraries(Observer pthread)

