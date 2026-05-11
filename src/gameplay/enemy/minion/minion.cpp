#include "minion.hpp"
#include "gameplay/projectile/plasma/plasma.hpp"
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
#include "gameplay/player/player.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include <cstddef>
#include <cstdlib>

using namespace Game;



void Minion::update(double dt, Engine::Systems& sys) {

    
    shot_cooldown.update(dt);

    if (shot_cooldown.past_limit()) {

        shot_cooldown.reset();

        float offsetY = 8.0f;
        float spreadAngle = 20.0f;  // Spread angle in degrees

        // Calculate diagonal directions
        float rad = spreadAngle * DEG2RAD;

        // Left-facing V
        sys.projectile->request_projectile<PlasmaProj>(
            Vector2{pos.x, pos.y - offsetY},
            Vector2Normalize(Vector2{-cosf(rad), -sinf(rad)}),
            80,
            true
        );

        sys.projectile->request_projectile<PlasmaProj>(
            pos.vec(),
            Vector2{-1, 0},
            80,
            true
        );

        sys.projectile->request_projectile<PlasmaProj>(
            Vector2{pos.x, pos.y + offsetY},
            Vector2Normalize(Vector2{-cosf(rad), sinf(rad)}),
            80,
            true
        );

    }

    if (pos.vec() == targets[cur_target]) {

        cur_target++;
        if (cur_target >= 4) 
            cur_target = 0;

        if (cur_target < 0)
            cur_target = 3;

    }

    pos = Vector2MoveTowards(pos.vec(), targets[cur_target], speed * dt);



};

void Minion::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
