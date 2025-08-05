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

    virtual bool is_foe() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual engine::Position get_position() = 0;
    virtual double get_speed() = 0;

    virtual void reset(engine::Position pos, double speed, bool active, Vector2 direction, bool foe) = 0;
};

}
