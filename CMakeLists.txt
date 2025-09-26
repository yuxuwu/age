cmake_minimum_required(VERSION 3.20.0)
project(age-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BIN "bin")
set(LIB "lib")
set(ASSETS "assets")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIB})

# Disable everything except JPEG and PNG
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XCF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_QOI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XPM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TGA OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PSD OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_HDR OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_IDPNG OFF CACHE BOOL "" FORCE)

# Enable only PNG and JPEG
set(SDLIMAGE_PNG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG ON CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/glm_1_0_1)
add_subdirectory(thirdparty/lua_5_4_8)
add_subdirectory(thirdparty/sol2_4_0_0)
add_subdirectory(thirdparty/entt_3_15_7)
add_subdirectory(thirdparty/sdl_3_2_22)
add_subdirectory(thirdparty/glad_gl_3_3)
add_subdirectory(thirdparty/imgui_1_92_3)
add_subdirectory(thirdparty/sdl_image_3_2_4)

add_executable(age-engine 
    src/Main.cpp 
    src/Game.cpp 
    src/util/FileReader.cpp
    src/shader/Shader.cpp
    src/shader/ShaderProgram.cpp)

target_link_libraries(age-engine PRIVATE glm sol2 entt SDL3::SDL3 glad_gl_3_3 imgui SDL3_image::SDL3_image)

add_custom_command(TARGET age-engine POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/${ASSETS}
        $<TARGET_FILE_DIR:age-engine>/${ASSETS})