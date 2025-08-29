#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "timer.hpp"
#include "shooting_machine.hpp"

namespace game {

class Player : public engine::IEntity{

public:

    Vector2 m_position;
    Vector2 m_direction;
    double m_speed = 150.0f;
    Rectangle m_hitbox;
    engine::Timer m_cooldown = engine::Timer(0.01f);
    ShootingMachine m_shooting_machine;

    Player() {

    }

    Player(Vector2 pos) :
    m_position(pos) {

        m_hitbox = Rectangle{pos.x, pos.y, 10.0f, 10.0f};

    }

    void update(double dt) override; 
    void draw() override;

};

}
