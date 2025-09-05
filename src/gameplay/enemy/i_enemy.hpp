#pragma once

#include "deps.hpp"
#include "entity.hpp"

namespace Game {

class IEnemy : public Engine::IEntity {

public:

    virtual void reset(Vector2 position) = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual void take_damage(EnemyMan& enemy_man) = 0;

};
    
}
