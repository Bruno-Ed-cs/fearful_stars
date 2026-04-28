#pragma once

#include "deps.hpp"

#include "entity.hpp"

namespace Game {

class Projectile : public Engine::Entity{
//    please have a default constructor
//    for the projectile manager

public:

    virtual void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0) = 0;
    //this will be responsible for trigerring self deletion
    virtual ~Projectile() = default;
};

}
