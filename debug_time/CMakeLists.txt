cmake_minimum_required(VERSION 3.1)
project(debug_time)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)

file(GLOB SRC_FILES "*.cc")
add_executable (${PROJECT_NAME} ${SRC_FILES})
