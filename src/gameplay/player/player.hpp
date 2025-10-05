#pragma once

#include "deps.hpp"

#include "i_entity.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include "shooting_machine.hpp"
#include "component.hpp"
#include "input_man.hpp"
#include "globals.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "shooting_machine.hpp"

namespace Game {

class ProjectileMan;
class EnemyMan;

class Player : public Engine::IEntity{

public:

    Player() {

        make_components();

    }

    Player(Vector2 pos) {

        make_components();
        components.get_component<Position>() = pos;

    }

    void update(double dt, Engine::Systems& sys) override; 
    void draw() override;
    Engine::ComponentContainer& get_components() override { return components; };

public:

    double speed = 150.0f;
    Engine::Timer cooldown = Engine::Timer(0.5f);
    ShootingMachine shooting_machine;
    Engine::ComponentContainer components;

private:

    void make_components() {

        components = Engine::ComponentContainer{
            new Position(0.0, 0.0),
            new Direction(0.0, 0.0),
            new Hitbox(10.0f, 10.0f),
            new Health(3)
        };

    }
};

}
