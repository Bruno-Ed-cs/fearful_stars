#include "component.hpp"
#include "deps.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "render_man.hpp"
#include "systems.hpp"

#include "basic_projectile.hpp"

using namespace Game;

void BasicProjectile::update(double dt, Engine::Systems& sys) {

    Vector2 movement = direction * speed * dt;

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


}


