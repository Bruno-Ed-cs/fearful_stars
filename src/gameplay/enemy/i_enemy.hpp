#pragma once

#include "deps.hpp"
#include "entity.hpp"

namespace Game {

class IEnemy : public Engine::IEntity {


    virtual void reset(Vector2 position) = 0;

};
    
}
