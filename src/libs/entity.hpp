#pragma once

namespace engine {

class IEntity {

public:

    virtual ~IEntity() = default;

    virtual void update(double dt) = 0;
    virtual void draw() = 0;


};

}
