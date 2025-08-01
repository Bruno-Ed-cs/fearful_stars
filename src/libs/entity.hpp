#pragma once

namespace engine {

class Entity {

public:

    virtual ~Entity() = default;

    virtual void update(double dt) = 0;
    virtual void draw() = 0;


};

}
