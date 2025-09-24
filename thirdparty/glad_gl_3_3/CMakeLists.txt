add_library(glad_gl_3_3 STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

target_include_directories(glad_gl_3_3 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")