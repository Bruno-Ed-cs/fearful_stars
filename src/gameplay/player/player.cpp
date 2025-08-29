#include "deps.hpp"

#include "player.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "shooting_machine.hpp"
#include "imgui.h"

using namespace Game;

void Player::update(double dt) {

    m_direction = {0,0};

    if (Engine::InputMan::is_event_active("move_right")) {

        m_direction.x = 1;

    }

    if (Engine::InputMan::is_event_active("move_up")) {

        m_direction.y = -1;

    }

    if (Engine::InputMan::is_event_active("move_down")) {

        m_direction.y = 1;

    }

    if (Engine::InputMan::is_event_active("move_left")) {

        m_direction.x = -1;

    }

    m_shooting_machine.run(this);

    m_cooldown.update(dt);


    m_direction = Vector2Normalize(m_direction);

    Vector2 movement = m_direction * (dt * m_speed);

    m_position += movement;

    m_position.x = Clamp(m_position.x, 0.0, Engine::g_canva_size.x);
    m_position.y = Clamp(m_position.y, 0.0, Engine::g_canva_size.y);

    m_hitbox.x = (m_position.x - m_hitbox.width / 2);
    m_hitbox.y = (m_position.y - m_hitbox.height / 2);

    //std::cout << m_position.get_round().x << " " << m_position.get_round().y << " " << m_direction.x << " " << m_direction.y <<'\n';
}

void Player::draw() {

    //DrawRectangleRec(m_hitbox, RED);
    Rectangle dest{m_position.x - 8, m_position.y - 8, 16.0f, 16};
    Rectangle origin{3 * 16, 0, -16, 16};
    DrawTexturePro(Assets::ship_tilemap, origin , dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawCircleV(m_position, 1.0f, GREEN);
    DrawCircleV(m_position, 0.5f, GRAY);



}
