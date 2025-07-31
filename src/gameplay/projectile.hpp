#pragma once
#include "position.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

namespace game {

class Projectile : public Entity {

public:

    Rectangle m_hitbox{0, 0, 5, 5};
    double m_speed;
    engine::Position m_position;
    Vector2 m_direction;

    Projectile(Vector2 direction, double speed, Vector2 spawn_point) :
        m_speed(speed), m_position(spawn_point), m_direction(direction) {}

    void update() override; 

    void draw() override; 


};

}
