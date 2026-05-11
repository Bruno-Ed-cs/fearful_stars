#include "plasma.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "raylib.h"
#include "render_man.hpp"

using namespace Game;

void PlasmaProj::update(double dt, Engine::Systems& sys) {

    auto dir = Vector2Normalize(orientation.vec());
    Vector2 movement = dir * speed * dt;

    this->pos += movement;

    if (foe) {

        if (CheckCollisionRecs(get_hitbox(), sys.player->get_player().get_hitbox())) {

            sys.player->get_player().take_damage();
            destruct = true;

        }

    } else {
        auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
        if (enemy_collision.has_collided) {

            if (!foe) {
                auto& enemy = sys.enemy->get_enemy(enemy_collision.enemy_ids.front());
                enemy.take_damage(sys, damage);
            }

            destruct = true; 
        }
    }

}


void PlasmaProj::draw() {

    Color tint = Color{0, 164, 255, 255};
    Color e_tint = Color{255, 78, 78, 255};

    if (!foe) {

        Rectangle source = Rectangle{0, 0, 15, 7};
        Rectangle view = Rectangle{pos.x - 8, pos.y -4, 15, 7};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        tint);

    } else {

        Rectangle source = Rectangle{0, 0, -15, 7};
        Rectangle view = Rectangle{pos.x - 8, pos.y -4, 15, 7};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        e_tint);

    }

}

void PlasmaProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = damage == 0 ? this->damage : damage;
    this->destruct = false;
}

