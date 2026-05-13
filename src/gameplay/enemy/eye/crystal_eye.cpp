#include "crystal_eye.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/projectile/plasma/plasma.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "raymath.h"
#include "gameplay/player/player.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include <cstddef>
#include <cstdlib>

using namespace Game;



void CrystalEye::update(double dt, Engine::GameState& sys) {

    shot_cooldown.update(dt);
    chain_cooldown.update(dt);

    if (shot_cooldown.past_limit()) {

        if (chain_cooldown.past_limit()) {
            shot_count++;
            chain_cooldown.reset();

            sys.projectile->emplace<PlasmaProj>(pos.vec(), Vector2{-1,0}, 100, true);

            if (shot_count >= 4) {
                shot_cooldown.reset();
                shot_count = 0;
            }

        }

    }

    if (target_pos.y == 0) {

        target_pos.x = (rand() % 270) + 50;
        target_pos.y = rand() % 180;
    }

    if (Vector2Equals(pos.vec(), target_pos)) {
        
        in_position = true;
    }

    if (!in_position) {

        pos = Vector2MoveTowards(pos.vec(), target_pos, speed * dt);
        direction.y = 1;

    } else {


        if (pos.y > 170)
            direction.y = -1;

        if (pos.y < 10)
            direction.y = 1;

        Vector2 movement = Vector2Normalize(direction.vec()) * (speed * dt);
        pos += movement;

    }

};

void CrystalEye::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
