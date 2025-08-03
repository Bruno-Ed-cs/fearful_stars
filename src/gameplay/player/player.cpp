#include "deps.hpp"

#include "player.hpp"
#include "globals.hpp"
#include "shooting_machine.hpp"

using namespace game;

void Player::update(double dt) {

    m_direction = {0,0};

    if (IsKeyDown(KEY_RIGHT)) {

        m_direction.x = 1;

    }

    if (IsKeyDown(KEY_UP)) {

        m_direction.y = -1;

    }

    if (IsKeyDown(KEY_DOWN)) {

        m_direction.y = 1;

    }

    if (IsKeyDown(KEY_LEFT)) {

        m_direction.x = -1;

    }

    m_shooting_machine.run(this);

    m_cooldown.update(dt);


    m_direction = Vector2Normalize(m_direction);

    Vector2 movement = m_direction * (dt * m_speed);

    m_position.move(movement);

    m_hitbox.x = (m_position.get_round().x - m_hitbox.width / 2);
    m_hitbox.y = ( m_position.get_round().y - m_hitbox.height / 2);

    //std::cout << m_position.get_round().x << " " << m_position.get_round().y << " " << m_direction.x << " " << m_direction.y <<'\n';
}

void Player::draw() {

    DrawRectangleRec(m_hitbox, RED);
    DrawCircleV(m_position.get_round(), 1.0f, GREEN);
    Rectangle dest{m_position.get_round().x, m_position.get_round().y, 16.0f, 16};
    Rectangle origin{0, 6 * 16, -16, 16};
    DrawTexturePro(assets::ship_tilemap, origin , dest, Vector2{0, 0}, 0.0f, WHITE);

}
