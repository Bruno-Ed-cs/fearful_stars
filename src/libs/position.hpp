#pragma once

#include "raylib.h"
#include "raymath.h"

namespace engine {

class Position {

    Vector2 m_real_pos;

public:

    Position() :
    m_real_pos(0, 0) {}

    Position(Vector2 pos) :
    m_real_pos(pos) {}

    Position(float x, float y) :
    m_real_pos(Vector2{x, y}) {}

    void move(Vector2 target) {

        m_real_pos = Vector2Add(target, m_real_pos);
    }

    Vector2 get_round() {

        Vector2 projection;
        projection.x = std::floor(m_real_pos.x) ;
        projection.y = std::floor(m_real_pos.y);

        return projection;
    }

    Vector2 get_real() {

        return m_real_pos;

    }

    Position get_copy() { return Position(m_real_pos);}

    void set_pos(Vector2 new_pos) { m_real_pos = new_pos; }



};

}
