cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

project(fearful_stars LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB_RECURSE files "src/*.cpp")

add_executable(${PROJECT_NAME} ${files})

target_include_directories(${PROJECT_NAME} PUBLIC include src/libs src)

include(raylib_options.txt)

add_subdirectory(dependencies/raylib-5.5 raylib)

target_link_libraries(${PROJECT_NAME} raylib)


target_precompile_headers(${PROJECT_NAME}
   PUBLIC src/deps.hpp)

make_directory(assets)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)   



