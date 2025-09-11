#include "deps.hpp"

#include "player.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "shooting_machine.hpp"
#include "imgui.h"

using namespace Game;

void Player::update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) {

    direction = {0,0};

    if (Engine::InputMan::is_event_active("move_right")) {

        direction.x = 1;

    }

    if (Engine::InputMan::is_event_active("move_up")) {

        direction.y = -1;

    }

    if (Engine::InputMan::is_event_active("move_down")) {

        direction.y = 1;

    }

    if (Engine::InputMan::is_event_active("move_left")) {

        direction.x = -1;

    }

    shooting_machine.run(this, projectile_man);

    cooldown.update(dt);


    direction = Vector2Normalize(direction);

    Vector2 movement = direction * (dt * speed);

    position += movement;

    position.x = Clamp(position.x, 0.0, Engine::g_canva_size.x);
    position.y = Clamp(position.y, 0.0, Engine::g_canva_size.y);

    hitbox.x = (position.x - hitbox.width / 2);
    hitbox.y = (position.y - hitbox.height / 2);

    //std::cout << position.get_round().x << " " << position.get_round().y << " " << direction.x << " " << direction.y <<'\n';
}

void Player::draw() {

    //DrawRectangleRec(hitbox, RED);
    Rectangle dest{position.x - 8, position.y - 8, 16.0f, 16};
    Rectangle origin{3 * 16, 0, -16, 16};
    DrawTexturePro(Assets::ship_tilemap, origin , dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawCircleV(position, 1.0f, GREEN);
    DrawCircleV(position, 0.5f, GRAY);

}
