#pragma once

#include "gameplay/enemy/enemy_man.hpp"

namespace Engine {

    void update_loop(double dt, Game::EnemyMan& enemy_man);
    void draw_loop(Game::EnemyMan& enemy_man);

}
