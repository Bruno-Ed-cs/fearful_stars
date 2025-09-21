#include "basic_enemy.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "raymath.h"
#include "gameplay/player/player_manager.hpp"

using namespace Game;


void BasicEnemy::draw() {

    auto& hitbox = dynamic_cast<Hitbox&>(components["Hitbox"]);

    DrawRectangleRec(hitbox.get(position), YELLOW);
};

void BasicEnemy::update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) {


    Player& player = player_man.get_player();
    if (Vector2Distance(player.position, position) > 50){
        if (direction == Vector2{0,1} && position.y > Engine::g_canva_size.y) 
            direction = Vector2{0, -1};

        if (direction == Vector2{0,-1} && position.y < 0) 
            direction = Vector2{0, 1};

        Vector2 movement = direction * speed;
        movement = Vector2Normalize(movement);
        position += movement;

    } else {


        position = Vector2MoveTowards(position, player.position, speed);
    }
};

void BasicEnemy::take_damage(EnemyMan& enemy_man) {

    Health& hp = dynamic_cast<Health&>(this->components["Health"]);

    hp.take_damage(1);

    if (hp.is_dead()){

        uint32_t id = enemy_man.get_enemy(this);

        enemy_man.append_delete_queue(id);
    }

}

void BasicEnemy::reset(Vector2 position) {

    position = position;

};
