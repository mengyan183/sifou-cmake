cmake_minimum_required(VERSION 3.17)
project(sifou_cmake)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sifou_cmake
        fork_process_demo.cpp
        fork_process_demo.h
        LICENSE
        README.md)
