#include "chaser.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "raymath.h"
#include "gameplay/player/player_manager.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include <cstddef>
#include <cstdlib>

using namespace Game;



void Chaser::update(double dt, Engine::Systems& sys) {

    player_pos_update.update(dt);

    if (player_pos_update.past_limit()) {

        player_pos_update.reset();
        player_pos = sys.player->get_player().pos.vec();

    }

    pos = Vector2MoveTowards(pos.vec(), player_pos, speed * dt);

};

void Chaser::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
