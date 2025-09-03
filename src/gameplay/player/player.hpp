#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "timer.hpp"
#include "shooting_machine.hpp"
#include "gameplay/enemy/enemy_man.hpp"

namespace Game {

class Player : public Engine::IEntity{

public:

    Vector2 m_position;
    Vector2 m_direction;
    double m_speed = 150.0f;
    Rectangle m_hitbox;
    Engine::Timer m_cooldown = Engine::Timer(0.01f);
    ShootingMachine m_shooting_machine;

    Player() {

    }

    Player(Vector2 pos) :
    m_position(pos) {

        m_hitbox = Rectangle{pos.x, pos.y, 10.0f, 10.0f};

    }

    void update(double dt, EnemyMan& enemy_man) override; 
    void draw() override;

};

}
