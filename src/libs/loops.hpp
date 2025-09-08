#pragma once

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

namespace Engine {

    void update_loop(double dt, Game::EnemyMan& enemy_man, Game::ProjectileMan& projectile_man);
    void draw_loop(Game::EnemyMan& enemy_man, Game::ProjectileMan& projectile_man);

}
