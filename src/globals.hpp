#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "winman.hpp"

namespace engine {

    inline std::vector<std::unique_ptr<engine::Entity>> g_bullets;
    inline std::unique_ptr<engine::WinMan> g_window;
    inline RenderTexture2D g_canva;

}

namespace game::assets {

    inline Texture2D ship_tilemap;

}
