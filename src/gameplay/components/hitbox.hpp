#pragma once

#include "deps.hpp"
#include "component.hpp"

namespace Game {

class Hitbox : public Engine::IComponent {

public:

    float width;
    float height;


public:

    Hitbox(float width, float height) :
        width(width), height(height) {};

    Rectangle get(Vector2 position) {

        return Rectangle{position.x - (width / 2), position.y - (height / 2), width, height};

    };

    std::string get_name() { return typeid(Hitbox).name(); };

};

}
