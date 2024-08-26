cmake_minimum_required(VERSION 3.26)
project(code C)

set(CMAKE_C_STANDARD 11)

add_executable(code main.c
        my_strings.h
        my_strings.c)
