#pragma once
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
    Vector2 m_position;
    Vector2 m_direction;

    Projectile(Vector2 direction, double speed, Vector2 spawn_point) :
        m_speed(speed), m_position(spawn_point), m_direction(direction) {}

    void update() override {

        //m_direction = Vector2Normalize(m_direction);
        std::cout << "Frame time: " << GetFrameTime() << '\n';
        std::cout << m_direction.y << " " << m_direction.x << '\n';
        std::cout << m_speed << '\n';
        Vector2 movement = Vector2Scale(m_direction, m_speed * GetFrameTime());

        //engine::vector2_round(movement);

        m_position = Vector2Add(m_position, movement);
        //m_position.x += 1.0f;

        m_hitbox.x = m_position.x;
        m_hitbox.y = m_position.y;

        std::cout << movement.x << " " << movement.y << '\n';
    }

    void draw() override {

        DrawRectangleRec(m_hitbox, BLUE);

    }


};

}
