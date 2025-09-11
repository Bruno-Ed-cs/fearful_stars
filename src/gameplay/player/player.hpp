#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "timer.hpp"
#include "shooting_machine.hpp"

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

public:


    Vector2 position;
    Vector2 direction;
    double speed = 150.0f;
    Rectangle hitbox;
    Engine::Timer cooldown = Engine::Timer(0.5f);
    ShootingMachine shooting_machine;

};

}
