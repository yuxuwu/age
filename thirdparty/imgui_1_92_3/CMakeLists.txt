set(IMGUI_SRC_FILES)

file(GLOB IMGUI_SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    )

add_library(imgui STATIC ${IMGUI_SRC_FILES})

target_include_directories(imgui PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/backends"
    )
target_link_libraries(imgui PUBLIC SDL3::SDL3)