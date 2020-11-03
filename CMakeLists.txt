cmake_minimum_required(VERSION 3.0.0)

project(balka)

set(SOURCES
        forces_and_moments.cpp
        lu_solver.cpp
        main.cpp
        parser.cpp
        balk.cpp)

set(HEADERS
        forces_and_moments.h
        lu_solver.h
        parser.h
        balk.h)

add_executable(balka ${SOURCES} ${HEADERS})

set_target_properties(
    balka PROPERTIES
    CMAKE_CXX_STANDARD 17
)
