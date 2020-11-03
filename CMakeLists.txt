cmake_minimum_required(VERSION 3.13.0)

set(SOURCES main.cpp balk.cpp forces_and_moments.cpp lu_solver.cpp main.cpp parser.cpp)

target_sources(balka PRIVATE ${SOURCES})
