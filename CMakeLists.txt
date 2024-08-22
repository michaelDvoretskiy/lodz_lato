cmake_minimum_required(VERSION 3.26)
project(code C)

set(CMAKE_C_STANDARD 11)

add_executable(code main.c
        operations_int.h
        operations_int.c
        operations_float.h
        operations_float.c
        operations_point.h
        operations_point.c
        calculator.h
        calculator.c)
