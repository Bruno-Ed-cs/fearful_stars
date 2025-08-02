cmake_minimum_required(VERSION 3.15)

project(fearful_stars)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(files 
    src/draw_loop.cpp
    src/gameplay/player/player.cpp
    src/gameplay/player/player_manager.cpp
    src/gameplay/projectile/basic_projectile.cpp
    src/gameplay/projectile/projectile_manager.cpp
    src/libs/utils.cpp
    src/main.cpp
    src/update_loop.cpp
)
add_executable(${PROJECT_NAME} src/main.cpp ${files})

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



