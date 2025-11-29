#include "upgrade_proj.hpp"
#include "gameplay/player/player_manager.hpp"
#include "raylib.h"


using namespace Game;

void UpgradeProj::update(double dt, Engine::Systems& sys) {

    Vector2 movement = Vector2Normalize(orientation.vec()) * (speed * dt);

    pos += movement;

    auto player_hitbox = sys.player->get_player().hitbox.get(sys.player->get_player().pos);

    if (CheckCollisionRecs(player_hitbox, hitbox.get(pos.vec()))) {

        destruct = true;
    }

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

