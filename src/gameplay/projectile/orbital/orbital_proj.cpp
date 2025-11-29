#include "orbital_proj.hpp"
#include "gameplay/player/player_manager.hpp"
#include "deps.hpp"
#include "raymath.h"
#include <cmath>

const double pi = std::numbers::pi;
using namespace Game;

double clamp_angle(double angle) {
    // Use modulo to properly wrap angles
    angle = fmod(angle, 2 * pi);
    if (angle < 0) angle += 2 * pi;
    return angle;
}

void OrbitalProj::update(double dt, Engine::Systems& sys) {

    pos = sys.player->get_player().pos;
    
    if (orientation.y > 0) {

        pos.y = pos.y + radius;

    } else if (orientation.y < 0) {

        pos.y = pos.y - radius;
    
    }

    auto collision_projs = sys.projectile->check_collisions(hitbox.get(pos.vec()), true);

    if (collision_projs.collided) {

        for (auto& id : collision_projs.targets) {

            sys.projectile->append_delete_queue(id);
        }

    }
}

void OrbitalProj::draw() {

}

void OrbitalProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;

}

