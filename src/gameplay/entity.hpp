#pragma once

namespace game {

class Entity {

public:

    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void draw() = 0;


};

}
