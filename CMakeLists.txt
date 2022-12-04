cmake_minimum_required(VERSION 3.17)
project(vychi_9)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(vychi_9
        A_B.cpp
        A_B.h
        begin.cpp
        begin.h
        extrapolation.cpp
        extrapolation.h
        interpolation.cpp
        interpolation.h
        main.cpp
        operators.cpp
        operators.h
        Runge_Kutta.cpp
        Runge_Kutta.h
        start_usl.h)
