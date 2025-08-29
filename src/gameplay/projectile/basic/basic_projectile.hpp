#pragma once

#include "deps.hpp"

#include "../i_projectile.hpp"
#include "timer.hpp"

namespace Game {

class BasicProjectile : public IProjectile {

public:

    BasicProjectile() = default;

    BasicProjectile(Vector2 position, Vector2 direction, double speed, bool foe) : 
        m_pos(position), m_direction(direction), m_speed(speed), m_foe(foe) {

        m_hitbox.y = position.y;
        m_hitbox.x = position.x;
    }

    bool is_foe() override { return m_foe; }
    Rectangle get_hitbox() override { return m_hitbox; }
    Vector2 get_position() override { return m_pos; }
    double get_speed() override { return m_speed; }

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe) override {

        m_pos = pos;
        m_speed = speed;
        m_direction = direction;
        m_foe = foe;

    }

    void update(double dt) override;
    void draw() override;

private:

    bool m_foe = false;
    Rectangle m_hitbox = Rectangle{0, 0, 5, 5};
    Vector2 m_pos;
    double m_speed = 0;
    Vector2 m_direction{0, 0};
};

}
