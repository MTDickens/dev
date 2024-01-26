cmake_minimum_required(VERSION 3.5)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O") 

# Find all *.cpp files in the current directory
file(GLOB SRCS *.cpp)

foreach(SRC ${SRCS})
    get_filename_component(EXECUTABLE_NAME ${SRC} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SRC})
endforeach()