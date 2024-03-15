cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Check if the SHUT_COUT option is provided
option(SHUT_COUT "Enable SHUT_COUT macro" OFF)

# Add a compile-time macro based on the SHUT_COUT option
if(SHUT_COUT)
    add_definitions(-DSHUT_COUT)
endif()

add_executable(main main.cpp)