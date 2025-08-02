#pragma once

#include "deps.hpp"

#include "position.hpp"
#include "projectile.hpp"

namespace game {

class BasicProjectile : public Projectile {

public:

    BasicProjectile(engine::Position position, Vector2 direction, double speed, bool foe) : 
        m_pos(position), m_direction(direction), m_speed(speed), m_foe(foe) {
    }

    bool is_active() override { return m_active; }
    bool is_foe() override { return m_foe; }
    Rectangle get_hitbox() override { return m_hitbox; }
    engine::Position get_position() override { return m_pos; }
    double get_speed() override { return m_speed; }

    void set_position(engine::Position pos) override { m_pos = pos; }

    void set_hitbox(Rectangle hitbox) override { m_hitbox = hitbox; }

    void set_speed(double speed) override { m_speed = speed; }

    void set_active(bool active) override { m_active = active; }

    void set_direction(Vector2 direction) override { m_direction = direction; }

    void set_foe(bool foe) override { m_foe = foe; }

    void update(double dt) override;
    void draw() override;

private:

    bool m_active = true;
    bool m_foe = false;
    Rectangle m_hitbox = Rectangle{0, 0, 5, 5};
    engine::Position m_pos{0, 0};
    double m_speed = 0;
    Vector2 m_direction{0, 0};

};

}
