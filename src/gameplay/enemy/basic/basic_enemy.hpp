#pragma once

#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/i_enemy.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

namespace Game {

class BasicEnemy : public IEnemy {

public:

    void draw() override;
    void update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man) override;
    void reset(Vector2 position) override;
    void take_damage(EnemyMan& enemy_man) override;
    Rectangle get_hitbox() override { return m_hitbox; };

    BasicEnemy(Vector2 position) :
        m_position(position) {};

    BasicEnemy() = default;

private:

    Vector2 m_position {200, 50};
    Rectangle m_hitbox {200, 200, 10, 10};
    Vector2 m_direction {0,1};
    double m_speed {1};

    
};

}
