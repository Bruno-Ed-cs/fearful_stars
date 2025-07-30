#pragma once
#include "raylib.h"
#include <cmath>

namespace engine {

void vector2_round(Vector2& vec) {

    vec.x = std::round(vec.x);
    vec.y = std::round(vec.y);

    return;
}

}
