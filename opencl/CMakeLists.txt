cmake_minimum_required(VERSION 3.1.0)
project(opencl_bits)

find_package(OpenCL REQUIRED)
find_package(OpenCV 3.4.3 REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CMAKE_CXX_STANDARD 11)

include_directories(include ${OpenCL_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
add_executable(set_id "src/set_id.cpp")
target_link_libraries(set_id ${OpenCL_LIBRARY})

add_executable(set_id_image "src/set_id_image.cpp")
target_link_libraries(set_id_image ${OpenCL_LIBRARY} ${OpenCV_LIBS})

add_executable(copy_image "src/copy_image.cpp")
target_link_libraries(copy_image ${OpenCL_LIBRARY} ${OpenCV_LIBS})
