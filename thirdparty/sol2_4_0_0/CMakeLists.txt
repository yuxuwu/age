add_library(sol2 STATIC sol2_pch.cpp)

target_include_directories(sol2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sol2/include")

target_link_libraries(sol2 PUBLIC lua)