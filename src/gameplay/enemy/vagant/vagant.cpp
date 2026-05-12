#include "vagant.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/projectile/orbital/orbital_proj.hpp"
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



void Vagant::update(double dt, Engine::Systems& sys) {

    shot_cooldown.update(dt);

    if (shot_cooldown.past_limit()) {

        shot_cooldown.reset();
        // Diamond pattern with 4 projectiles and 7x7 empty center
        Vector2 center = pos.vec();  // Your BrokenShip's position

        // Diamond pattern - 4 projectiles at up, down, left, right
        // Adjust offset to create 7x7 empty box (3.5 units radius)
        float offset = 9.0f;  // Offset from center for 7x7 gap

        // 1. Up projectile
        sys.projectile->emplace<OrbitalProj>(
            Vector2{center.x, center.y - offset},  // Position: above center
            Vector2{0, -1},                        // Direction: straight up
            70,                                    // Speed
            true                                   // Foe flag
        );

        // 2. Down projectile
        sys.projectile->emplace<OrbitalProj>(
            Vector2{center.x, center.y + offset},  // Position: below center
            Vector2{0, 1},                         // Direction: straight down
            70,                                    // Speed
            true                                   // Foe flag
        );

        // 3. Left projectile
        sys.projectile->emplace<OrbitalProj>(
            Vector2{center.x - offset, center.y},  // Position: left of center
            Vector2{-1, 0},                        // Direction: straight left
            70,                                    // Speed
            true                                   // Foe flag
        );

        // 4. Right projectile
        sys.projectile->emplace<OrbitalProj>(
            Vector2{center.x + offset, center.y},  // Position: right of center
            Vector2{1, 0},                         // Direction: straight right
            70,                                    // Speed
            true                                   // Foe flag
        );
    }

    Vector2 movement = Vector2Normalize(direction.vec()) * dt * speed;
    pos += movement;

};

void Vagant::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
