#pragma once

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/levels/levels.hpp"
#include "globals.hpp"
#include "systems.hpp"

void update_loop(double dt, Engine::Systems& sys) {

    sys.projectile->update(dt, sys);
    sys.enemy->update(dt, sys);
    sys.player->update(dt, sys);
    sys.level->update(dt);

}
