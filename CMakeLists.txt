cmake_minimum_required(VERSION 3.27)
project(GraphAlg)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(GraphAlg main.cpp
        graph.cpp
        graph.h
        oStack.h
        oQueue.h
        oPQueue.h
        Graph-ics.cpp
        Graph-ics.h)

target_compile_features(GraphAlg PRIVATE cxx_std_17)
target_link_libraries(GraphAlg PRIVATE SFML::Graphics)

configure_file(
        ${CMAKE_SOURCE_DIR}/assets/NotoSans.ttf
        ${CMAKE_BINARY_DIR}/assets/NotoSans.ttf
        COPYONLY
)
