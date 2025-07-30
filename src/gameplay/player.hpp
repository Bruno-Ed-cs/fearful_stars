#pragma once

#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include "utils.hpp"

namespace game {

class Player {

public:

    Vector2 m_position{0,0};
    Vector2 m_direction{0,0};
    double m_speed = 120.0f;
    Rectangle m_hitbox{m_position.x, m_position.y, 10, 10};


    void update() {

        m_direction = {0,0};

        if (IsKeyDown(KEY_RIGHT)) {

            m_direction.x = 1;

        }

        if (IsKeyDown(KEY_UP)) {

            m_direction.y = -1;

        }

        if (IsKeyDown(KEY_DOWN)) {

            m_direction.y = 1;

        }

        if (IsKeyDown(KEY_LEFT)) {

            m_direction.x = -1;

        }

        m_direction = Vector2Normalize(m_direction);

        Vector2 movement = (m_direction * m_speed) * GetFrameTime();

        engine::vector2_round(movement);

        m_position = Vector2Add(m_position, movement);

        m_hitbox.x = m_position.x;
        m_hitbox.y = m_position.y;

        std::cout << m_position.x << " " << m_position.y << " " << m_direction.x << " " << m_direction.y <<'\n';
    }

};

}
