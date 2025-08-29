#pragma once

#include "deps.hpp"

#include "entity.hpp"

namespace Game {

class IProjectile : public Engine::IEntity{
//    please have a default constructor
//    for the projectile manager

public:

    virtual bool is_foe() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual Vector2 get_position() = 0;
    virtual double get_speed() = 0;

    virtual void reset(Vector2 pos, double speed, Vector2 direction, bool foe) = 0;

    virtual ~IProjectile() = default;
};

}
