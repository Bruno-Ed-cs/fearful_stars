#include "deps.hpp"

#include "basic_projectile.hpp"

using namespace game;

void BasicProjectile::update(double dt) {

    Vector2 movement = m_direction * m_speed * dt;

    m_pos.move(movement);

    m_hitbox.x = m_pos.get_real().x;
    m_hitbox.y = m_pos.get_real().y;

//    std::cout << m_pos.get_real().x << " " << m_pos.get_real().y << '\n';
}

void BasicProjectile::draw() {

    DrawRectangleRec(m_hitbox, BLUE);

}
