cmake_minimum_required(VERSION 4.0)
project(laba17)

set(CMAKE_CXX_STANDARD 20)

add_executable(laba17 main.cpp
        tree.h
        helpers.cpp
        helpers.h
        io.cpp
        io.h
        validator.h
        zadania.cpp
        zadania.h
)
