#pragma once
#include "deps.hpp"
#include "raymath.h"


class Direction {

public:
    float x;
    float y;

public:

    Direction() :
    x(0), y(0) {}

    Direction (float x, float y) :
    x(x), y(y) {};

    Direction(Vector2 pos) :
    x(pos.x), y(pos.y) {};

    Vector2 vec() { return Vector2Normalize(Vector2{x, y}); };

    void operator=(Vector2 pos) {

        pos = Vector2Normalize(pos);

        x = pos.x;
        y = pos.y;
    };

};

