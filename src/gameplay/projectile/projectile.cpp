#include "projectile.hpp"

using namespace game;

void Projectile::update(double dt) {

    //m_direction = Vector2Normalize(m_direction);
    //std::cout << "Frame time: " << GetFrameTime() << '\n';
    //std::cout << m_direction.y << " " << m_direction.x << '\n';
    //std::cout << m_speed << '\n';
    Vector2 movement = m_direction * (dt * m_speed);

    //engine::vector2_round(movement);

    m_position.move(movement);
    //m_position.x += 1.0f;

    m_hitbox.x = m_position.get_pos().x;
    m_hitbox.y = m_position.get_pos().y;

    //std::cout << movement.x << " " << movement.y << '\n';
}

void Projectile::draw() {

    DrawRectangleRec(m_hitbox, BLUE);

}
