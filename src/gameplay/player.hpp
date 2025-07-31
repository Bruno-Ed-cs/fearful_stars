#pragma once

#include "gameplay/projectile.hpp"
#include "globals.hpp"
#include "position.hpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include "utils.hpp"
#include "entity.hpp"
#include "globals.hpp"
#include "projectile.hpp"

namespace game {

class Player : public Entity{

public:

    engine::Position m_position;
    Vector2 m_direction;
    double m_speed = 100.0f;
    Rectangle m_hitbox;

    Player(Vector2 pos) :
    m_position(pos) {

        m_hitbox = Rectangle{pos.x, pos.y, 10.0f, 10.0f};

    }

    void update() override; 
    void draw() override;

};

}
