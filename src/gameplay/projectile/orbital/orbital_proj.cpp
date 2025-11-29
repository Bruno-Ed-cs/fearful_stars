#include "orbital_proj.hpp"
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
    if (anchor.x == 0 && anchor.y == 0) {
        // Initialize anchor to player position + offset
        anchor = pos.vec(); // Start to the right of player
        anchor.x += radius;
    }

    // Get current angle and update it
    double current_angle = atan2(pos.y - anchor.y, pos.x - anchor.x);
    double angle = current_angle + speed * dt;
    angle = clamp_angle(angle);

    // Calculate new position using proper orbital mechanics
    pos.x = anchor.x + radius * std::cos(angle);
    pos.y = anchor.y + radius * std::sin(angle);
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

