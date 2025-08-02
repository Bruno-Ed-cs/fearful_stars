#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "position.hpp"

namespace game {

class Projectile : public engine::Entity{
//    please have a constructor like this:
//    for the projectile manager
//    Constructor(engine::Position position, Vector2 direction, double speed, bool foe)

public:

    virtual void reset_deadtime(double limit) = 0;
    virtual bool is_deadtime_over() = 0;
    virtual void update_deadtime(double dt) = 0;

    virtual bool is_active() = 0;
    virtual bool is_foe() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual engine::Position get_position() = 0;
    virtual double get_speed() = 0;
    virtual void set_position(engine::Position pos) = 0;
    virtual void set_hitbox(Rectangle hitbox) = 0;
    virtual void set_speed(double speed) = 0;
    virtual void set_active(bool active) = 0;
    virtual void set_direction(Vector2 direction) = 0;
    virtual void set_foe(bool foe) = 0;
};

}
