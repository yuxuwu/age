cmake_minimum_required(VERSION 3.20.0)
project(age-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BIN "bin")
set(LIB "lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIB})

add_subdirectory(thirdparty/glm_1_0_1)
add_subdirectory(thirdparty/lua_5_4_8)
add_subdirectory(thirdparty/sol2_4_0_0)
add_subdirectory(thirdparty/entt_3_15_7)
add_subdirectory(thirdparty/sdl_3_2_22 EXCLUDE_FROM_ALL)

add_executable(age-engine src/Main.cpp)

target_link_libraries(age-engine PRIVATE glm sol2 entt SDL3::SDL3)
