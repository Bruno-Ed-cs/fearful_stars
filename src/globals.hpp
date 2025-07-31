#pragma once

#include "gameplay/entity.hpp"
#include "gameplay/projectile.hpp"
#include "raylib.h"
#include "winman.hpp"
#include <memory>
#include <vector>

namespace engine {

    inline std::vector<std::unique_ptr<game::Entity>> g_bullets;
    inline engine::WinMan* g_window;
    inline RenderTexture2D g_canva;

}
