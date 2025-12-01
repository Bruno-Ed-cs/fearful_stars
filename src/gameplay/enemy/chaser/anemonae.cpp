#include "anemonae.hpp"
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
#include "gameplay/player/player_manager.hpp"
#include "systems.hpp"
#include "timer.hpp"

using namespace Game;


void BrokenShip::draw() {


};

void BrokenShip::update(double dt, Engine::Systems& sys) {

    Vector2 movement = Vector2Normalize(direction.vec()) * dt * speed;
    this->pos += movement;

};

void BrokenShip::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
