#pragma once

#include "deps.hpp"

#include "i_entity.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "winman.hpp"

namespace Engine {

    inline std::unique_ptr<Engine::WinMan> g_window;
    inline RenderTexture2D g_canva;
    inline Vector2 g_canva_size;
    inline bool g_debug = false;

}

namespace Game::Assets {

    inline Texture2D ship_tilemap;

}


