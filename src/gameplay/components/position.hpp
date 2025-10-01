#pragma once
#include "deps.hpp"
#include "component.hpp"

namespace Game {

class Position : public Engine::IComponent {

public:
    float x;
    float y;

public:

    Position(float x, float y) :
    x(x), y(y) {};

    Position(Vector2 pos) :
    x(pos.x), y(pos.y) {};

    Vector2 vec() { return Vector2{x, y}; };

    void operator=(Vector2 pos) {
        x = pos.x;
        y = pos.y;
    };

    void operator+=(Vector2 pos) {

        x += pos.x;
        y += pos.y;

    }

    std::string get_name() override { return typeid(Position).name(); };
};

}
