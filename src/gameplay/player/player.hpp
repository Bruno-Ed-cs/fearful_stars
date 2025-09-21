#pragma once

#include "deps.hpp"

#include "i_entity.hpp"
#include "timer.hpp"
#include "shooting_machine.hpp"
#include "component.hpp"

namespace Game {

class ProjectileMan;
class EnemyMan;

class Player : public Engine::IEntity{

public:

    Player() {

    }

    Player(Vector2 pos) :
    position(pos) {

        hitbox = Rectangle{pos.x, pos.y, 10.0f, 10.0f};

    }

    void update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) override; 
    void draw() override;
    Engine::ComponentContainer& get_components() override { return components; };

public:


    Vector2 position;
    Vector2 direction;
    double speed = 150.0f;
    Rectangle hitbox;
    Engine::Timer cooldown = Engine::Timer(0.5f);
    ShootingMachine shooting_machine;
    Engine::ComponentContainer components;

};

}
