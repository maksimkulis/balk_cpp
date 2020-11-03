cmake_minimum_required(VERSION 3.13.0)

project(Balka VERSION 1.0.0)

add_executable(balka)
target_include_directories(balka PRIVATE ${PROJECT_SOURCE_DIR}/include)
set_target_properties(balka PROPERTIES COMPILE_FLAGS --std=c++17)
add_subdirectory(src)
