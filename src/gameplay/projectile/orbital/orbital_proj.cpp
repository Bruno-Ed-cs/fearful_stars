#include "orbital_proj.hpp"
#include "render_man.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "deps.hpp"
#include "raymath.h"
#include "timer.hpp"
#include <cmath>

using namespace Game;

void OrbitalProj::update(double dt, Engine::Systems& sys) {

    if (!foe) {
        pos = sys.player->get_player().pos;

        if (orientation.y > 0) {

            pos.y = pos.y + radius;

        } else if (orientation.y < 0) {

            pos.y = pos.y - radius;

        }

        auto collision_projs = sys.projectile->check_collisions(hitbox.get(pos.vec()), true);

        if (collision_projs.collided) {

            for (auto& id : collision_projs.targets) {

                sys.projectile->append_delete_queue(id);
            }

        }

        auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
        if (enemy_collision.has_collided) {

            if (!foe) {
                auto& enemy = sys.enemy->get_enemy(enemy_collision.enemy_ids.front());
                enemy.take_damage(sys, damage);
            }

            destruct = true; 
        }
    } else {

        lifetime.update(dt);

        if (lifetime.past_limit())
            destruct = true;

    }
}

void OrbitalProj::draw() {
    Color tint = Color{111, 236, 255, 255};
    Color e_tint = Color{255, 78, 78, 255};

    if (!foe) {

        Rectangle source = Rectangle{0, 0, 6, 6};
        Rectangle view = Rectangle{pos.x - 3, pos.y -3, 6, 6};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        tint);

    } else {

        Rectangle source = Rectangle{0, 0, 6, 6};
        Rectangle view = Rectangle{pos.x - 3, pos.y -3, 6, 6};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        e_tint);

    }

}

void OrbitalProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;
    this->lifetime.reset();

}

