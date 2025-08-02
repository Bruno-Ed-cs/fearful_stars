#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "winman.hpp"

namespace engine {

    inline std::unique_ptr<engine::WinMan> g_window;
    inline RenderTexture2D g_canva;
    inline Vector2 g_canva_size;

}

namespace game::assets {

    inline Texture2D ship_tilemap;

}
