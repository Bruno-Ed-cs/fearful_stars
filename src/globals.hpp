#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "winman.hpp"

namespace Engine {

    extern "C" {
    inline Vector2 g_world_size;
    inline bool g_debug = false;
    inline bool g_running = true;
    }

}


