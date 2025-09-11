#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

#include "basic_projectile.hpp"

using namespace Game;

void BasicProjectile::update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) {

    Vector2 movement = direction * speed * dt;

    pos += movement;

    hitbox.x = pos.x;
    hitbox.y = pos.y;

    if (!foe) {

        EnemyMan::Collision collision = enemy_man.check_collisions(hitbox);

        if (collision.has_collided) {

            IEnemy& enemy = enemy_man.get_enemy(collision.enemy_id);
            enemy.take_damage(enemy_man);

            uint32_t id = projectile_man.get_id(this);
            projectile_man.append_delete_queue(id);


        }


    } 

//    std::cout << pos.get_real().x << " " << pos.get_real().y << '\n';
}

void BasicProjectile::draw() {

    DrawRectangleRec(hitbox, BLUE);

}
