#pragma once

#include "deps.hpp"

#include "entity.hpp"
#include "position.hpp"

namespace game {

class Projectile : public engine::Entity{
//    please have a default constructor
//    for the projectile manager

public:

    virtual bool is_foe() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual engine::Position get_position() = 0;
    virtual double get_speed() = 0;

    virtual void reset(engine::Position pos, double speed, Vector2 direction, bool foe) = 0;
};

}
