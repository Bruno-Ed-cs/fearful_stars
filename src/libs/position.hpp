#pragma once

#include "raylib.h"
#include "raymath.h"
#include <cmath>
namespace engine {

class Position {

    Vector2 m_real_pos;

public:

    Position(Vector2 pos) :
    m_real_pos(pos) {}

    void move(Vector2 target) {

        m_real_pos = Vector2Add(target, m_real_pos);
    }

    Vector2 get_pos() {

        Vector2 projection;
        projection.x = std::floor(m_real_pos.x) ;
        projection.y = std::floor(m_real_pos.y);

        return projection;
    }


};

}
