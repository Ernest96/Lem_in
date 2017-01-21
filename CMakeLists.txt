cmake_minimum_required(VERSION 3.6)
project(21_lemin)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    ft_strsplit.c
    func.c
    func1.c
    func2.c
    func3.c
    func4.c
    func5.c
    func6.c
    func7.c
    get_next_line.c
    lem_in.c)

add_executable(21_lemin ${SOURCE_FILES})