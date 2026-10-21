#include "game.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "raylib.h"


Actor Player::make() {

    Actor player {};
    player.type = Actor::Player;
    player.speed = 135.0f;
    player.special_meter = 0;
    player.upgrade = 0;
    player.cooldown = Engine::Timer(0.5f);
    player.graze_cooldown = Engine::Timer(0.10);
    player.primary_level = 1;
    player.secondary_level = 0;
    player.aux_level = 0;
    player.shooting_sound = Engine::AssetMan::get_sound("space-laser");
    player.spritesheet = Engine::AssetMan::get_texture("player_ship");
    player.pos = Position(30.0, 30.0);
    player.dir = Direction(0.0, 0.0);
    player.hitbox = Hitbox(2.0f, 2.0f);
    player.graze_range = Hitbox(42, 30);
    player.lives = Health(5);
    player.dead = false;
    player.invincible = false;
    player.self_destruct = false;

    return player;
}

void Player::update(Actor& player) {

    Vector2 direction = {0,0};

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

    double dt = GetFrameTime();
    Vector2 movement;


    if (Engine::InputMan::is_event_active("slowdown")) {

        movement = direction * (dt * (player.speed * 0.6));

    } else {

        movement = direction * (dt * player.speed);

    }

    //std::println("movement = x{} y{}", movement.x, movement.y);


    player.pos += movement;

    player.pos.x = Clamp(player.pos.x, 0.0, Engine::g_world_size.x);
    player.pos.y = Clamp(player.pos.y, 0.0, Engine::g_world_size.y);

    std::println("Player pos : {}, {}", player.pos.x, player.pos.y);
}

void Player::draw(Actor& player) {

    Rectangle dest{player.pos.x - 14, player.pos.y - 8, 26, 16};
    Rectangle origin{0, 0, 26, 16};

    if (player.invincible) {
        DrawTexturePro(*player.spritesheet, origin, dest, {0,0}, 0.0, WHITE);
    }
    else {
        DrawTexturePro(*player.spritesheet, origin, dest, {0,0}, 0.0, RED);
    }

}
