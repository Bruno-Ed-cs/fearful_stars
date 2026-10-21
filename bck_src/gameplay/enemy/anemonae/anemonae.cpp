#include "anemonae.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy.hpp"
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



void Anemonae::update(double dt, Engine::GameState& sys) {

    if (final_x == 0) {
        final_x = (rand() % 90) + 150;
    }

    shot_cooldown.update(dt);

    if (shot_cooldown.past_limit()) {
        shot_cooldown.reset();

        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{-1, 0}, 70, true);
        // 1. Left
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{-1, 0}, 70, true);

        // 2. Right  
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{1, 0}, 70, true);

        // 3. Up
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{0, -1}, 70, true);

        // 4. Down
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{0, 1}, 70, true);
        // 5. Up-Left
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{-0.707f, -0.707f}, 70, true);

        // 6. Up-Right
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{0.707f, -0.707f}, 70, true);

        // 7. Down-Left
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{-0.707f, 0.707f}, 70, true);

        // 8. Down-Right
        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{0.707f, 0.707f}, 70, true);
    }


    this->pos = Vector2MoveTowards(pos.vec() , Vector2{final_x, pos.y}, speed * dt);

};

void Anemonae::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
