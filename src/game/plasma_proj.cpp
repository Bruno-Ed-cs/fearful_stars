#include "game.hpp"
#include "raylib.h"

Projectile PlasmaProjectile::make(Position pos, Direction dir, int damage, double speed) {

    auto plasma = Projectile();

    plasma.pos = pos;
    plasma.direction = dir;
    plasma.hitbox = Hitbox(10, 6);
    plasma.base_damage = damage;
    plasma.damage_output = plasma.base_damage;
    plasma.speed = speed;
    plasma.self_destruct = false;
    plasma.spritesheet = "plasma_proj_ani";
    // Engine::Animator animation = Engine::Animator({15, 7}, 24, 
    //         {{.size = 6, .index = 0, .name = "fly"}});

    plasma.animation = Engine::Animator{"animations/plasma_proj"};

    return plasma;

}

void PlasmaProjectile::update(idx self, Game& gm, bool foe) {

    auto& plasma = foe? gm.enemy_proj[self] : gm.player_proj[self];
    double dt = GetFrameTime();
    plasma.animation.update(dt);
    auto dir = Vector2Normalize(plasma.direction.vec());
    Vector2 movement = dir * plasma.speed * dt;

    plasma.pos += movement;

    if (plasma.damage_output <= 0) {

        if (foe) {
            gm.enemy_proj.deactivate(self);

        } else {
            gm.player_proj.deactivate(self);
        }

    }

    // if (foe) {
    //
    //     if (CheckCollisionRecs(get_hitbox(), sys.player->get_player().get_hitbox())) {
    //
    //         sys.player->get_player().take_damage();
    //         destruct = true;
    //
    //     }
    //
    // } else {
    //     auto enemy_collision = sys.enemy->check_collisions(hitbox.get(pos));
    //     if (enemy_collision.has_collided) {
    //
    //         if (!foe) {
    //             auto& enemy = sys.enemy->get_enemy(enemy_collision.enemy_ids.front());
    //             enemy.take_damage(sys, damage);
    //         }
    //
    //         destruct = true; 
    //     }
    // }

}
