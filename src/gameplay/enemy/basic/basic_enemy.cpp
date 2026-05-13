#include "basic_enemy.hpp"
#include "render_man.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "raymath.h"
#include "gameplay/player/player.hpp"
#include "systems.hpp"
#include "timer.hpp"

using namespace Game;


void BasicEnemy::draw() {


    Rectangle sorce = Rectangle{0, 0, hitbox.width, hitbox.height};

    Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                    *sprite,
                                    hitbox.get(pos.vec()),
                                    sorce,
                                    0,
                                    0,
                                    WHITE);


};

void BasicEnemy::update(double dt, Engine::Systems& sys) {

    Vector2 movement = Vector2Normalize(direction.vec()) * dt * speed;
    pos += movement;

};

void BasicEnemy::take_damage(Engine::Systems& sys, int damage) {


    hp.take_damage(damage);

    if (hp.is_dead()){

        uint32_t id = sys.enemy->get_enemy(this);

        self_destruct = true;
    }

}

void BasicEnemy::reset(Vector2 position) {

    this->pos = position;
    this->hp.restore();

};
