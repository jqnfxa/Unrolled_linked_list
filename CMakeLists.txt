cmake_minimum_required(VERSION 3.26)
project(Algorithms_lb1)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(Algorithms_lb1 main.cpp
        Timer.cpp
        Timer.hpp
        UnrolledLinkedList.cpp
        UnrolledLinkedList.hpp
        Node.cpp
        Node.hpp
        Generator.cpp
        Generator.hpp
)
