#pragma once

#include "deps.hpp"
#include "gameplay/enemy/i_enemy.hpp"

namespace Game {

class BasicEnemy : public IEnemy {

public:

    void draw() override;
    void update(double dt) override;
    void reset(Vector2 position) override;

private:

    Vector2 m_position {200, 50};
    Rectangle m_hitbox {200, 200, 10, 10};
    Vector2 m_direction {0,1};
    double m_speed {5};
    
};

}
