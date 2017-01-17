cmake_minimum_required(VERSION 3.5)
project(16_lem_in)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    lem_in.c)

add_executable(16_lem_in ${SOURCE_FILES})