#pragma once

#include "component.hpp"
#include "deps.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/i_enemy.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "raylib.h"
#include "systems.hpp"

namespace Game {

class BasicEnemy : public IEnemy {

public:

    Engine::ComponentContainer components;

    BasicEnemy():
    pos(Vector2{100, 100}){};

    BasicEnemy(Vector2 position) :
        pos(position) {};


    void draw() override;
    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;
    Rectangle get_hitbox() override { return hitbox.get(pos.vec()); };
    void take_damage(Engine::Systems& sys, int damage) override;
    EnemyType get_type() override { return EnemyType::basic; };
    bool destroy_self() override { return self_destruct; };
    Vector2 get_position() override { return pos.vec(); };


public:

    Vector2 direction {0,1};
    double speed {70};
    Health hp = Health(2);
    Hitbox hitbox = Hitbox(10.0, 10.0);
    Position pos;

    bool self_destruct = false;

private:


};

}
