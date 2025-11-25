#include "gameplay/player/primary_shots/plasma_shot.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/plasma/plasma.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "input_man.hpp"

using namespace Game;

void PlasmaShooter::run(Player& player, ProjectileMan& projectile_man, double dt) {

    switch (player.primary_level) {

        case 1:

            idle_cooldown.set_limit(0.5);
            idle_cooldown.update(dt);

        break;

        case 2:
        break;

        case 3:
        break;
    
    }

    while(state_func(this, player, projectile_man));
}

bool PlasmaShooter::idle(Player& player, ProjectileMan& projectile_man) {

    if (Engine::InputMan::is_event_active("shoot")) {
        if (idle_cooldown.past_limit()) {

            idle_cooldown.reset();

            switch (player.primary_level) {

                case 1: 
                    state_func = &PlasmaShooter::shoot;
                    return true;
                    break;

            }

        }
    }

    return false;

}

bool PlasmaShooter::chain_shot(Player& player, ProjectileMan& projectile_man) {
    return true;

}

bool PlasmaShooter::shoot(Player& player, ProjectileMan& projectile_man) {

    auto position = player.pos.vec();
    auto direction = Direction(1, 0);
    double speed = 140;

    projectile_man.request_projectile<PlasmaProj>(position, direction.vec(), speed, false);

    state_func = &PlasmaShooter::idle;
    return false;
}
