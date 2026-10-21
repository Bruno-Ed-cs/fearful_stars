#include "broken_ship.hpp"
#include "gameplay/components/direction.hpp"
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
#include <cstdlib>
#include <ctime>

using namespace Game;





void BrokenShip::update(double dt, Engine::GameState& sys) {

    shot_cooldown.update(dt);
    pick_direction.update(dt);

    Vector2 center = Vector2{160, 90};  
    float distanceFromCenter = Vector2Distance(pos.vec(), center);

    if (pick_direction.past_limit()) {


        pick_direction.reset();

        direction.x = (rand() % 3) - 1;  // -1, 0, or 1
        direction.y = (rand() % 3) - 1;  // -1, 0, or 1

        if (pos.y > 160)
            direction.y = -1;

        if (pos.y < 20)
            direction.y = 1;


    } 

    if (distanceFromCenter > 90) {
        Vector2 toCenter = Vector2Subtract(center, pos.vec());
        direction = Vector2Normalize(toCenter);
    } 

    if (shot_cooldown.past_limit()) {

        shot_cooldown.reset();

        sys.projectile->emplace<BasicProjectile>(pos.vec(), Vector2{-1, 0}, 90, true);

    }

    Vector2 movement = Vector2Normalize(direction.vec()) * (dt * speed);

    this->pos += movement;

};

void BrokenShip::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
