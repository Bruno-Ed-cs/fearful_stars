#include "missile_proj.hpp"
#include "gameplay/components/direction.hpp"
#include "raymath.h"
#include "timer.hpp"
#include "gameplay/enemy/enemy_man.hpp"

using namespace Game;

void MissileProj::update(double dt, Engine::Systems& sys) {

    dorment_time.update(dt);

    //std::println("timer: {}", dorment_time.get_time());

    orientation = Vector2Normalize(orientation.vec());

    if (dorment_time.past_limit()) {

        orientation = Direction(1, 0);
        auto collisions = sys.enemy->check_collisions(search_area.get(pos));

        if (collisions.has_collided){

            Vector2 target = sys.enemy->get_enemy(collisions.enemy_ids.front()).get_position();

            pos = Vector2MoveTowards(pos.vec(), target, speed * dt);

        } else {
            Vector2 movement = orientation.vec() * (speed * dt);
            pos += movement;
        }


    } else {

        //std::println("falling");

        if (pos.y > 160 || pos.y < 20) {
            dorment_time.set_limit(0.0);
        }
        Vector2 movement = orientation.vec() * ((speed/2) * dt);
        pos += movement;

    }

    auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
    if (enemy_collision.has_collided) {

        if (!foe) {
            auto& enemy = sys.enemy->get_enemy(enemy_collision.enemy_ids.front());
            enemy.take_damage(sys, damage);
        }

        destruct = true; 
    }
}

void MissileProj::draw() {

}

void MissileProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;
    this->dorment_time.set_limit(0.25f);
    this->dorment_time.reset();

}

