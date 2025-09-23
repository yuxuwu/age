cmake_minimum_required(VERSION 3.20.0)
project(age-engine)

set(BIN "bin")
set(LIB "lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIB})

add_subdirectory(thirdparty/glm_1_0_1)

add_executable(age-engine src/Main.cpp)

target_link_libraries(age-engine PRIVATE glm)

set_property(TARGET age-engine PROPERTY CXX_STANDARD 17)