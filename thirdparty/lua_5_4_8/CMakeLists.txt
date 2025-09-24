set(LUA_SRC_FILES)

file(GLOB LUA_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(lua STATIC ${LUA_SRC_FILES})

target_include_directories(lua PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
