cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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


# file(GLOB_RECURSE files "src/*.cpp")

set(files 

    "src/engine/background_man.cpp"
    "src/engine/input_man.cpp"
    "src/engine/render_man.cpp"
    "src/engine/asset_man.cpp"
    "src/engine/music_man.cpp"
    "src/engine/debugger.cpp"
    "src/systems.cpp"
    #    "src/gameplay/enemy/vagant/vagant.cpp"
    #    "src/gameplay/enemy/chaser/chaser.cpp"
    #    "src/gameplay/enemy/eye/crystal_eye.cpp"
    #    "src/gameplay/enemy/basic/basic_enemy.cpp"
    #    "src/gameplay/enemy/enemy_man.cpp"
    #    "src/gameplay/enemy/minion/minion.cpp"
    #    "src/gameplay/enemy/anemonae/anemonae.cpp"
    #    "src/gameplay/enemy/broken_ship/broken_ship.cpp"
    #    "src/gameplay/projectile/orbital/orbital_proj.cpp"
    #    "src/gameplay/projectile/missile/missile_proj.cpp"
    #    "src/gameplay/projectile/plasma/plasma.cpp"
    #    "src/gameplay/projectile/basic/basic_projectile.cpp"
    #    "src/gameplay/projectile/upgrade/upgrade_proj.cpp"
    #    "src/gameplay/projectile/projectile_manager.cpp"
    #    "src/gameplay/projectile/big_shot/bigshot_proj.cpp"
    #    "src/gameplay/player/aux_powers/orbital_shield.cpp"
    #    "src/gameplay/player/primary_shots/basic_shot.cpp"
    #    "src/gameplay/player/primary_shots/plasma_shot.cpp"
    "src/gameplay/player/player.cpp"
    #    "src/gameplay/player/special_shots/big_shooter.cpp"
    # "src/gameplay/player/player_manager.cpp"
    #    "src/gameplay/player/secondary_shots/missile_shooter.cpp"
    "src/gameplay/ui/ui_man.cpp"
    #    "src/gameplay/levels/levels.cpp"
    "src/main.cpp"



)


file(GLOB imgui_files "dependencies/dear_imgui/*.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug") 

    add_library(game SHARED ${files})
    add_executable(${PROJECT_NAME} src/dev_runner.cpp)
else()

    add_library(game STATIC ${files})
    add_executable(${PROJECT_NAME} src/prod_runner.cpp)
endif()

include_directories(include src/engine src)

include(raylib_options.txt)

add_subdirectory(dependencies/raylib-5.5 raylib)


if (${HOT_RELOADING})

    add_library(imgui STATIC ${imgui_files})
    target_compile_options(imgui PRIVATE -fPIC -rdynamic)

    add_library(imgui-raylib STATIC dependencies/raylib-imgui/rlImGui.cpp)
    target_compile_options(imgui-raylib PRIVATE -fPIC -rdynamic)

    target_link_libraries(game imgui-raylib imgui raylib)
    target_link_libraries(${PROJECT_NAME})

else()

    add_library(imgui STATIC ${imgui_files})
    target_compile_options(imgui PRIVATE -fPIC -rdynamic)

    add_library(imgui-raylib STATIC dependencies/raylib-imgui/rlImGui.cpp)
    target_compile_options(imgui-raylib PRIVATE -fPIC -rdynamic)

    target_link_libraries(game raylib imgui-raylib imgui)
    target_link_libraries(${PROJECT_NAME} game)

endif()

target_precompile_headers(game PUBLIC src/deps.hpp)

make_directory(assets)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)   



