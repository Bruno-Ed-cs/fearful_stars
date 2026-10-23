#include "game.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "raymath.h"
#include "state_machine.hpp"

enum BasicShot {
    Idle = 1,
    Shooting
};

int basic_idle(Actor& player, Game& gm) {

    if (player.shooting_cooldown.past_limit())
        return Shooting;

    return 0;

}

int basic_shooting(Actor& player, Game& gm) {

    player.shooting_cooldown.reset(0.5);

    gm.player_proj.activate(PlasmaProjectile::make(
                            player.pos,
                            {1, 0},
                            1,
                            player.speed * 2));

    return Idle;
}


void basic_shot_machine (Actor& player, Game& gm) {

    if (player.primary_state == 0) {
        player.primary_state = Idle;
    }

    for (int i = 0; i < 10 && player.primary_state != 0; i ++) {

        switch (static_cast<BasicShot>(player.primary_state)) {

            case BasicShot::Idle: player.primary_state = basic_idle(player, gm); break;
            case BasicShot::Shooting: player.primary_state =  basic_shooting(player, gm); break;

        }

    }

};


Actor Player::make(Position pos) {

    Actor player {};
    player.type = Actor::Player;
    player.speed = 145.0f;
    player.special_meter = 0;
    player.upgrade = 0;
    player.cooldown = Engine::Timer(0.5f);
    player.graze_cooldown = Engine::Timer(0.10);
    player.primary_level = 1;
    player.secondary_level = 0;
    player.aux_level = 0;
    player.shooting_sound = "space-laser";
    player.spritesheet = "player_ship";
    player.pos = pos;
    player.dir = Direction(0.0, 0.0);
    player.hitbox = Hitbox(2.0f, 2.0f);
    player.graze_range = Hitbox(42, 30);
    player.lives = Health(5);
    player.dead = false;
    player.invincible = false;
    player.shooting_cooldown = Engine::Timer(0);

    return player;
}

void Player::update(idx self, Game& gm) {

    auto& player = gm.actors[self];

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

    if (Engine::InputMan::is_event_active("shoot")) {

        basic_shot_machine(player, gm);
        

    }

    double dt = GetFrameTime();

    player.shooting_cooldown.update(dt);
    player.cooldown.update(dt);

    Vector2 movement;

    direction = Vector2Normalize(direction);

    if (Engine::InputMan::is_event_active("slowdown")) {

        movement = direction * (dt * (player.speed * 0.6));

    } else {

        movement = direction * (dt * player.speed);

    }

    //std::println("movement = x{} y{}", movement.x, movement.y);


    player.pos += movement;

    player.pos.x = Clamp(player.pos.x, 0.0, Engine::g_world_size.x);
    player.pos.y = Clamp(player.pos.y, 0.0, Engine::g_world_size.y);

    // std::println("Player pos : {}, {}", player.pos.x, player.pos.y);
}

void Player::draw(Actor& player) {

    Rectangle dest{player.pos.x - 14, player.pos.y - 8, 26, 16};
    Rectangle origin{0, 0, 26, 16};

    Texture2D sprite = Engine::AssetMan::get_texture(player.spritesheet);

    if (!player.invincible) {
        DrawTexturePro(sprite, origin, dest, {0,0}, 0.0, WHITE);
    }
    else {
        DrawTexturePro(sprite, origin, dest, {0,0}, 0.0, RED);
    }

}
