#pragma once

#include "systems.hpp"

namespace Engine {

class ComponentContainer;

class IEntity {

public:

    virtual ~IEntity() = default;

    virtual void update(double dt, Systems& sys) = 0;
    virtual void draw() = 0;
    virtual ComponentContainer get_components() = 0;


};

}
