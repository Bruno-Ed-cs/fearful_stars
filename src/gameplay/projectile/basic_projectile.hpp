#pragma once

#include "deps.hpp"

#include "position.hpp"
#include "projectile.hpp"
#include "timer.hpp"

namespace game {

class BasicProjectile : public Projectile {

public:

    BasicProjectile(engine::Position position, Vector2 direction, double speed, bool foe) : 
        m_pos(position), m_direction(direction), m_speed(speed), m_foe(foe) {

        m_hitbox.y = position.get_real().y;
        m_hitbox.x = position.get_real().x;
    }

    bool is_foe() override { return m_foe; }
    Rectangle get_hitbox() override { return m_hitbox; }
    engine::Position get_position() override { return m_pos; }
    double get_speed() override { return m_speed; }

    void reset(engine::Position pos, double speed, bool active, Vector2 direction, bool foe) override {

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
    engine::Position m_pos;
    double m_speed = 0;
    Vector2 m_direction{0, 0};
};

}
