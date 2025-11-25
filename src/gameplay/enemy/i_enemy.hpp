#pragma once

#include "deps.hpp"
#include "i_entity.hpp"

namespace Game {

enum class EnemyType {
    basic,


};

class IEnemy : public Engine::IEntity {

public:

    virtual void reset(Vector2 position) = 0;
    virtual void take_damage(EnemyMan& enemy_man, int damage) = 0;
    virtual EnemyType get_type() = 0;

    virtual Rectangle get_hitbox() = 0;
    virtual Vector2 get_position() = 0;
    

};
    
}
