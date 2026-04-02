cmake_minimum_required(VERSION 3.27)
project(GraphAlg)

set(CMAKE_CXX_STANDARD 20)

add_executable(GraphAlg main.cpp
        graph.cpp
        graph.h
        oStack.h
        oQueue.h
        oPQueue.h)
