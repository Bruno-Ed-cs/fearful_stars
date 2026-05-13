#include "component.hpp"
#include "deps.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "globals.hpp"
#include "raymath.h"
#include "render_man.hpp"
#include "systems.hpp"

#include "basic_projectile.hpp"

using namespace Game;

void BasicProjectile::update(double dt, Engine::GameState& sys) {

    
    Vector2 movement = Vector2Normalize(direction) * speed * dt;

    pos += movement;

    if (!foe) {

        EnemyMan::Collision collision = sys.enemy->check_collisions(hitbox.get(pos.vec()));

        if (!collision.enemy_ids.empty()) {

            this->self_destruct = true;
        }

    } else {

        auto player_hitbox = sys.player->get_player().hitbox.get(sys.player->get_player().pos.vec());
        if (CheckCollisionRecs(player_hitbox, hitbox.get(pos.vec()))) {

            sys.player->get_player().take_damage();

        }
    
    }

//    std::cout << pos.get_real().x << " " << pos.get_real().y << '\n';
}

void BasicProjectile::draw() {
    Color tint = Color{111, 236, 255, 255};
    Color e_tint = Color{255, 78, 78, 255};

    if (!foe) {

        Rectangle source = Rectangle{0, 0, 5, 5};
        Rectangle view = Rectangle{pos.x - 2, pos.y -2, 5, 5};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        tint);

    } else {

        Rectangle source = Rectangle{0, 0, -5, 5};
        Rectangle view = Rectangle{pos.x - 2, pos.y -2, 5, 5};

        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                        *sprite,
                                        view,
                                        source,
                                        0,
                                        0,
                                        e_tint);

    }

}


