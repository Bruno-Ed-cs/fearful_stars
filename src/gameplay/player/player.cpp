#include "deps.hpp"
// #include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "gameplay/components.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include "timer.hpp"

#include "player.hpp"


using namespace Game;

//void upgrader(Player& player) {
//
//
//    switch (player.upgrade) {
//
//        case 0:
//            break;
//
//        case 1:
//
//            if (player.primary_level >= 3)
//                break;
//
//            player.primary_level++;
//            player.primary_level = std::clamp(player.primary_level, 1, 3);
//            player.upgrade -= 1;
//
//            break;
//
//        case 2:
//
//            if (player.secondary_level >= 2)
//                break;
//
//            player.secondary_level++;
//            player.secondary_level = std::clamp(player.secondary_level, 0, 2);
//            player.upgrade -= 2;
//
//            break;
//
//        case 3:
//
//            if (player.aux_level >= 2)
//                break;
//
//            player.aux_level++;
//            player.aux_level = std::clamp(player.aux_level, 0, 2);
//            player.upgrade -= 3;
//
//            break;
//
//        default:
//
//            sys.comp.health[player.lives].points++;
//            player.upgrade -= 4;
//
//            break;
//
//    }
//
//
//}

void Player::update(double dt, Engine::Systems& sys) {

    static Engine::Timer press_colldown = Engine::Timer(0.5);
    press_colldown.update(dt);

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

    if (Engine::InputMan::is_event_active("upgrade")) {



        if (press_colldown.past_limit()) {

            press_colldown.reset();
            //upgrader(*this);
        }

    }


    //primary_shot->run(*this, *sys.projectile, dt);
    //secondary_shot->run(*this, sys, dt);
    //special_shot->run(*this, sys, dt);
    //aux_power->run(*this, sys, dt);

    direction = Vector2Normalize(direction);


    Vector2 movement;


    if (Engine::InputMan::is_event_active("slowdown")) {

        movement = direction * (dt * (speed * 0.6));

    } else {

        movement = direction * (dt * speed);

    }

    //std::println("movement = x{} y{}", movement.x, movement.y);

    Position& pos = comp.position[this->pos];

    pos += movement;

    pos.x = Clamp(pos.x, 0.0, sys.world_size.x);
    pos.y = Clamp(pos.y, 0.0, sys.world_size.y);

//    if (sys.projectile->check_collisions(graze_range.get(pos.vec()), true).collided && graze_cooldown.past_limit()) {
//
//        graze_cooldown.reset();
//
//        special_meter += 2;
//        special_meter = std::clamp(special_meter, 0, 100);
//    }
//
//    if (invis_timer.past_limit()) 
//        invincible = false;
//
//    auto collisions_proj_foe = sys.projectile->check_collisions(hitbox.get(pos.vec()), true);
//    auto collisions_proj = sys.projectile->check_collisions(hitbox.get(pos.vec()), false);
//    auto collisions_enemy = sys.enemy->check_collisions(hitbox.get(pos.vec()));
//
//    if (collisions_proj_foe.collided ||
//        collisions_enemy.has_collided) {
//
//        take_damage();
//
//    }
//
//    if (collisions_proj.collided) {
//
//        for (auto& id : collisions_proj.targets) {
//
//            auto& proj = sys.projectile->get_projectile(id);
//
//            if (proj.get_type() == typeid(UpgradeProj)) {
//
//                upgrade++;
//                sys.projectile->append_delete_queue(id);
//
//            }
//
//        }
//
//    }
//
//
//
//    if (lives.points == 0) {
//
//        die(sys);
//
//    }
//
//
    //std::cout << position.get_round().x << " " << position.get_round().y << " " << direction.x << " " << direction.y <<'\n';
}

void Player::take_damage(Engine::Systems& sys) {

    if (!invincible) {
        comp.health[this->lives].take_damage(1);
        turn_invincible(2);
    }
}

void Player::die(Engine::Systems& sys) {

    dead = true;

}

void Player::revive(Engine::Systems& sys) {

    comp.health[this->lives].restore();
    dead = false;

}

void Player::turn_invincible(double seconds) {

    invincible = true;

    if (seconds < 0)
        return;

    invis_timer = Engine::Timer(seconds);
}

void Player::draw(Engine::Systems& sys) {

    Position& pos = sys.comp.position[this->pos];

    Rectangle dest{pos.x - 12, pos.y - 8, 24, 16};
    Rectangle origin{0, 0, 24, 16};

    if (invincible) {
        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle, *spritesheet, dest, origin, 0, 0, RED);

    }
    else Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle, *spritesheet, dest, origin);

}

