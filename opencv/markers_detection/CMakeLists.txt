cmake_minimum_required(VERSION 3.0.1)
project(markers_detection)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "-Wall")
set (CMAKE_CXX_STANDARD 11)

include_directories( include ${OpenCV_INCLUDE_DIRS} )
file(GLOB SOURCE_FILES "src/detectors/*.cc")
add_executable(${PROJECT_NAME} "src/main.cc" ${SOURCE_FILES} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
