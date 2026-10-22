#pragma once

#include "deps.hpp"


namespace Engine {

    extern Vector2 g_world_size;
    extern bool g_debug;
    extern bool g_running;

    extern int save_slot;
    extern std::string level_path;

    bool in_world_bounds(Vector2 pos);
    bool in_world_bounds(Vector2 pos, int padding);

}


