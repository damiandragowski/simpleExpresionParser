cmake_minimum_required (VERSION 3.5)

project(main)

set(SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

set(CMAKE_BUILD_TYPE Debug)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable (main ${SOURCES})

