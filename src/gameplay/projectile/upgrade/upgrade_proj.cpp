#include "upgrade_proj.hpp"
#include "gameplay/player/player_manager.hpp"
#include "raylib.h"


using namespace Game;

void UpgradeProj::update(double dt, Engine::Systems& sys) {

    Vector2 movement = Vector2Normalize(orientation.vec()) * (speed * dt);

    pos += movement;

}

void UpgradeProj::draw() {

}

void UpgradeProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;

}

