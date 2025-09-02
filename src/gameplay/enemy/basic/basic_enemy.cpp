#include "basic_enemy.hpp"
#include "globals.hpp"
#include "raymath.h"

using namespace Game;


void BasicEnemy::draw() {

    DrawRectangleRec(m_hitbox, YELLOW);
};

void BasicEnemy::update(double dt) {

    m_hitbox.x = m_position.x - m_hitbox.width/2;
    m_hitbox.y = m_position.y - m_hitbox.height/2;

    if (m_direction == Vector2{0,1} && m_position.y > Engine::g_canva_size.y) 
        m_direction = Vector2{0, -1};

    if (m_direction == Vector2{0,-1} && m_position.y < 0) 
        m_direction = Vector2{0, 1};

    Vector2 movement = m_direction * m_speed;
    movement = Vector2Normalize(movement);
    m_position += movement;

};

void BasicEnemy::reset(Vector2 position) {

    m_position = position;

};

