#include "plasma.hpp"
#include "gameplay/enemy/enemy_man.hpp"

using namespace Game;

void PlasmaProj::update(double dt, Engine::Systems& sys) {

    auto dir = Vector2Normalize(orientation.vec());
    Vector2 movement = dir * speed * dt;

    this->pos += movement;

    auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
    if (enemy_collision.has_collided) {

       destruct = true; 
    }

}

void PlasmaProj::draw() {

}

void PlasmaProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = damage == 0 ? this->damage : damage;
    this->destruct = false;
}

