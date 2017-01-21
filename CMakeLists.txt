cmake_minimum_required(VERSION 3.5)
project(16_lem_in)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        func.c
        func1.c
        func2.c
        func3.c
        func4.c
        func5.c
        func6.c
        func7.c
        ft_strsplit.c
        get_next_line.c
    lem_in.c)

add_executable(16_lem_in ${SOURCE_FILES})