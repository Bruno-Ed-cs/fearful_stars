#include "basic_enemy.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "raymath.h"
#include "gameplay/player/player_manager.hpp"
#include "systems.hpp"

using namespace Game;


void BasicEnemy::draw() {

    auto& hitbox = components.get_component<Hitbox>();

    DrawRectangleRec(hitbox.get(position), YELLOW);
};

void BasicEnemy::update(double dt, Engine::Systems& sys) {

    Player& player = sys.player->get_player();
    Position& pos = player.components.get_component<Position>();

    if (Vector2Distance(pos.vec(), position) > 50){
        if (direction == Vector2{0,1} && position.y > Engine::g_canva_size.y) 
            direction = Vector2{0, -1};

        if (direction == Vector2{0,-1} && position.y < 0) 
            direction = Vector2{0, 1};

        Vector2 movement = direction * speed;
        movement = Vector2Normalize(movement);
        position += movement;

    } else {

        position = Vector2MoveTowards(position, pos.vec(), speed);
    }
};

void BasicEnemy::take_damage(EnemyMan& enemy_man, int damage) {

    Health& hp = components.get_component<Health>();

    hp.take_damage(damage);

    if (hp.is_dead()){

        uint32_t id = enemy_man.get_enemy(this);

        enemy_man.append_delete_queue(id);
    }

}

void BasicEnemy::reset(Vector2 position) {

    position = position;

};
