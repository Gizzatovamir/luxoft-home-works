cmake_minimum_required(VERSION 3.19)
project(DrySoft)

set(CMAKE_CXX_STANDARD 14)

add_executable(DrySoft ../main.cpp ../MoveBase.h ../Service.h ../logging.h)

target_link_libraries(DrySoft pthread)
