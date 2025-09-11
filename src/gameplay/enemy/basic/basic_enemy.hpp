#pragma once

#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/i_enemy.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

namespace Game {

class BasicEnemy : public IEnemy {

public:

    BasicEnemy(Vector2 position) :
        position(position) {};

    BasicEnemy() = default;

    void draw() override;
    void update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) override;
    void reset(Vector2 position) override;
    void take_damage(EnemyMan& enemy_man) override;
    Rectangle get_hitbox() override { return hitbox; };


public:

    Vector2 position {200, 50};
    Rectangle hitbox {200, 200, 10, 10};
    Vector2 direction {0,1};
    double speed {1};



    
};

}
