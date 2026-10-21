#include "bigshot_proj.hpp"
#include "render_man.hpp"
#include "raymath.h"
#include "gameplay/enemy/enemy.hpp"

using namespace Game;

void BigShotProj::update(double dt, Engine::GameState& sys) {

    orientation = Vector2Normalize(orientation.vec());
    Vector2 movement = orientation.vec() * dt * speed;

    pos += movement;

    auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
    if (enemy_collision.has_collided) {

        if (!foe) {

            for (auto& id : enemy_collision.enemy_ids) {
                auto& enemy = sys.enemy->get_enemy(id);
                enemy.take_damage(sys, damage);
            }
        }

    }
}

void BigShotProj::draw() {
    Color tint = Color{111, 236, 255, 255};
    Color e_tint = Color{255, 78, 78, 255};

    if (!foe) {

        Rectangle source = Rectangle{0, 0, 92, 64};
        Rectangle view = Rectangle{pos.x - 46, pos.y -32, 92, 64};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        tint);

    } else {

        Rectangle source = Rectangle{0, 0, 92, 64};
        Rectangle view = Rectangle{pos.x - 46, pos.y -32, -92, 64};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        e_tint);

    }

}

void BigShotProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;

}

