cmake_minimum_required(VERSION 3.16.0)
project(age-engine)

set(BIN "bin")
set(LIB "lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIB})

add_executable(age-engine src/Main.cpp)

set_property(TARGET age-engine PROPERTY CXX_STANDARD 17)