#pragma once

#include "deps.hpp"
#include "i_entity.hpp"

namespace Game {

class IEnemy : public Engine::IEntity {

public:

    virtual void reset(Vector2 position) = 0;
    virtual void take_damage(EnemyMan& enemy_man) = 0;
    virtual Vector2 get_position() = 0;


};
    
}
