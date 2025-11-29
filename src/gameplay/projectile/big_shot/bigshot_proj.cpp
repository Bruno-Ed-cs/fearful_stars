#include "bigshot_proj.hpp"
#include "raymath.h"
#include "gameplay/enemy/enemy_man.hpp"

using namespace Game;

void BigShotProj::update(double dt, Engine::Systems& sys) {

    orientation = Vector2Normalize(orientation.vec());
    Vector2 movement = orientation.vec() * dt * speed;

    pos += movement;

    auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
    if (enemy_collision.has_collided) {

        if (!foe) {

            for (auto& id : enemy_collision.enemy_ids) {
                auto& enemy = sys.enemy->get_enemy(id);
                enemy.take_damage(sys, damage);
            }
        }

    }
}

void BigShotProj::draw() {

}

void BigShotProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;

}

