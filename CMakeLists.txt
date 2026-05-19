cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

project(fearful_stars LANGUAGES CXX)
# Enable better debugging
# Print variables for debugging
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===== CONFIGURE ROCKSDB BEFORE add_subdirectory =====
# Disable treating warnings as errors
set(FAIL_ON_WARNINGS OFF CACHE BOOL "Disable warnings as errors" FORCE)
# Disable test compilation
set(WITH_TESTS OFF CACHE BOOL "Disable RocksDB test compilation" FORCE)
# Disable tools compilation
set(WITH_TOOLS OFF CACHE BOOL "Disable RocksDB tools compilation" FORCE)
# Set portable build (disable architecture-specific optimizations that may cause warnings)
set(PORTABLE ON CACHE BOOL "Build portable binary" FORCE)

add_subdirectory(dependencies/raylib-5.5 raylib)
add_subdirectory(dependencies/rocks_db rocksdb)

file(GLOB_RECURSE files "src/*.cpp")
file(GLOB imgui_files "dependencies/dear_imgui/*.cpp")

add_executable(${PROJECT_NAME} ${files})

include_directories(include src/engine src)

include(raylib_options.txt)


add_library(imgui STATIC ${imgui_files})

add_library(imgui-raylib STATIC dependencies/raylib-imgui/rlImGui.cpp)

target_link_libraries(${PROJECT_NAME} raylib imgui-raylib imgui rocksdb)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/deps.hpp)

make_directory(assets)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)   



