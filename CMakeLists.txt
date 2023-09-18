cmake_minimum_required(VERSION 3.26)
project(Algorithms_lb1)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(Algorithms_lb1 main.cpp
        src/Timer.cpp
        src/Timer.hpp
        src/UnrolledLinkedList.cpp
        src/UnrolledLinkedList.hpp
        src/Node.cpp
        src/Node.hpp
        src/Generator.cpp
        src/Generator.hpp
)
