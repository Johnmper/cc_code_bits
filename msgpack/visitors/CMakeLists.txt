cmake_minimum_required(VERSION 3.1)
project(pupil_visitor)

set(CMAKE_CXX_STANDARD 11)

find_package(msgpack REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIRS
    NAMES zmq.hpp
    PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
)
find_library(ZeroMQ_LIBS
    NAMES zmq
    PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
)


include_directories(${msgpack_INCLUDE_DIRS})

file(GLOB SRC_FILES "*.cc")
add_executable (${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${ZeroMQ_LIBS} ${msgpack_LIBS})
