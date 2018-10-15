cmake_minimum_required(VERSION 3.1)
project(stringhash)

add_compile_options(-Wall -O3)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC_FILES "*.cc")
add_executable (${PROJECT_NAME} ${SRC_FILES})
