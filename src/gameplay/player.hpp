#pragma once

#include "deps.hpp"

#include "position.hpp"
#include "entity.hpp"

namespace game {

class Player : public Entity{

public:

    engine::Position m_position;
    Vector2 m_direction;
    double m_speed = 125.0f;
    Rectangle m_hitbox;

    Player() {}

    Player(Vector2 pos) :
    m_position(pos) {

        m_hitbox = Rectangle{pos.x, pos.y, 10.0f, 10.0f};

    }

    void update(double dt) override; 
    void draw() override;

};

}
