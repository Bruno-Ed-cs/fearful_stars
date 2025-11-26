#include "gameplay/player/primary_shots/plasma_shot.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/plasma/plasma.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "input_man.hpp"

using namespace Game;

void PlasmaShooter::run(Player& player, ProjectileMan& projectile_man, double dt) {

    this->dt = dt;

    switch (player.primary_level) {
        case 1:

            idle_cooldown.set_limit(0.4);

        break;

        case 2:
            idle_cooldown.set_limit(0.3);
            chain_cooldown.set_limit(0.08);
        break;

        case 3:

            idle_cooldown.set_limit(0.25);
            chain_cooldown.set_limit(0.08);
        break;
    }

    while(state_func(this, player, projectile_man));
}

bool PlasmaShooter::idle(Player& player, ProjectileMan& projectile_man) {


    idle_cooldown.update(dt);

    if (idle_cooldown.past_limit()) {

        if (Engine::InputMan::is_event_active("shoot")){
            idle_cooldown.reset();

            switch (player.primary_level) {

                case 1: 

                    state_func = &PlasmaShooter::shoot_lv1;
                    return true;

                break;

                case 2:

                    state_func = &PlasmaShooter::shoot_lv2;
                    return true;

                break;

                case 3:

                    state_func = &PlasmaShooter::shoot_lv3;
                    return true;

                break;

            }
        }
    }

    return false;

}


bool PlasmaShooter::shoot_lv1(Player& player, ProjectileMan& projectile_man) {

    auto position = player.pos.vec();
    auto direction = Direction(1, 0);
    double speed = 140;

    projectile_man.request_projectile<PlasmaProj>(position, direction.vec(), speed, false);

    state_func = &PlasmaShooter::idle;
    return false;
}

bool PlasmaShooter::shoot_lv2(Player& player, ProjectileMan& projectile_man) {

    auto position = player.pos.vec();
    auto direction = Direction(1, 0);
    double speed = 180;


    if (chain_cooldown.past_limit() && this->shot) {
        chain_cooldown.reset();

        position.y += 5;
        projectile_man.request_projectile<PlasmaProj>(position, direction.vec(), speed, false);

        std::println("p2");

        state_func = &PlasmaShooter::idle;
        shot = false;
        return false;

    } else if (this->shot) {

        chain_cooldown.update(dt);
        std::println("p3");
        return false;
    }

    position.y -= 5;
    projectile_man.request_projectile<PlasmaProj>(position, direction.vec(), speed, false);
    shot = true;

    std::println("p1");
    return false;

}

bool PlasmaShooter::shoot_lv3(Player& player, ProjectileMan& projectile_man) {
    auto position = player.pos.vec();
    auto direction = Direction(1, 0);
    double speed = 190;


    if (chain_cooldown.past_limit() && this->shot) {
        chain_cooldown.reset();

        Vector2 pos1 = position;
        Vector2 pos2 = position;

        pos1.y += 8;
        pos2.y -= 8;

        projectile_man.request_projectile<PlasmaProj>(pos1, direction.vec(), speed, false);
        projectile_man.request_projectile<PlasmaProj>(pos2, direction.vec(), speed, false);

        std::println("p2");

        state_func = &PlasmaShooter::idle;
        shot = false;
        return false;

    } else if (this->shot) {

        chain_cooldown.update(dt);
        std::println("p3");
        return false;
    }

    projectile_man.request_projectile<PlasmaProj>(position, direction.vec(), speed, false);
    shot = true;

    std::println("p1");
    return false;

}

