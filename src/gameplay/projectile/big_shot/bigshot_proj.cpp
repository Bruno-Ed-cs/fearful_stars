#include "bigshot_proj.hpp"
#include "raymath.h"

using namespace Game;

void BigShotProj::update(double dt, Engine::Systems& sys) {

    orientation = Vector2Normalize(orientation.vec());
    Vector2 movement = orientation.vec() * dt * speed;

    pos += movement;

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

