#pragma once

#include "systems.hpp"

namespace Engine {

class ComponentContainer;

using Package = std::map<std::string, std::string>;
class Entity {

public:

    virtual ~Entity() = default;

    virtual void update(double dt, GameState& sys) = 0;
    virtual void draw() = 0;
    virtual bool destroy_self() = 0;
    virtual Package package() = 0;


};

}
