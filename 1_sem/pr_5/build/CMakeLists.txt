cmake_minimum_required(VERSION 3.8)

project(pr_5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pr_5 ../pr_5.cpp)

target_link_libraries(pr_5 pthread)

