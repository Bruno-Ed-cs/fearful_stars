#include "basic_enemy.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "raymath.h"
#include "gameplay/player/player_manager.hpp"
#include "systems.hpp"
#include "timer.hpp"

using namespace Game;


void BasicEnemy::draw() {


    DrawRectangleRec(hitbox.get(pos.vec()), YELLOW);
};

void BasicEnemy::update(double dt, Engine::Systems& sys) {

    Player& player = sys.player->get_player();

    if (Vector2Distance(pos.vec(), player.pos.vec()) > 50){
        if (direction == Vector2{0,1} && pos.y > Engine::g_world_size.y) 
            direction = Vector2{0, -1};

        if (direction == Vector2{0,-1} && pos.y < 0) 
            direction = Vector2{0, 1};

        Vector2 movement = direction * speed * dt;
        pos += movement;

        static Engine::Timer shot_time{0.2};

        shot_time.update(dt);
        if (shot_time.past_limit()) {
            shot_time.reset();

            sys.projectile->request_projectile<BasicProjectile>(pos.vec(), Vector2{-1, 0}, 120, true);
        }

    } else {

        pos = Vector2MoveTowards(pos.vec(), player.pos.vec(), speed * dt);
    }


};

void BasicEnemy::take_damage(EnemyMan& enemy_man, int damage) {


    hp.take_damage(damage);

    if (hp.is_dead()){

        uint32_t id = enemy_man.get_enemy(this);

        self_destruct = true;
    }

}

void BasicEnemy::reset(Vector2 position) {

    position = position;

};
