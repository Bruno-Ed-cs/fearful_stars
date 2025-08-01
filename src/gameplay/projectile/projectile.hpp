#pragma once

#include "deps.hpp"

#include "position.hpp"

namespace game {

class Projectile{

public:

    virtual bool is_foe() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual engine::Position get_position() = 0;
};

}
