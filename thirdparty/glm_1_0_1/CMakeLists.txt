add_library(glm STATIC glm_pch.cpp)

target_include_directories(glm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")