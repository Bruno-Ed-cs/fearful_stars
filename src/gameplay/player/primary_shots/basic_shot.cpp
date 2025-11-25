#include "gameplay/player/primary_shots/basic_shot.hpp"

#include "gameplay/player/player.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "input_man.hpp"

using namespace Game;

void BasicShot::run(Player& player, ProjectileMan& projectile_man, double dt) {

    while (state_func(this, player, projectile_man));
}

bool BasicShot::idle(Player& player, ProjectileMan& projectile_man) {

    if(player.cooldown.past_limit() && Engine::InputMan::is_event_active("shoot")) {

        player.cooldown.reset();
        state_func = &BasicShot::shoot;
        return true;

    } 

    state_func = &BasicShot::idle;
    return false;

}

bool BasicShot::shoot(Player& player, ProjectileMan& projectile_man) { 

    double proj_speed = 200.0f;
    Vector2 direction{1, 0};
    bool foe = false;
    Vector2 pos = player.pos.vec();
    pos += Vector2{0, -3};

    projectile_man.request_projectile<BasicProjectile>(pos, direction, proj_speed, foe);
    PlaySound(*player.shooting_sound);


    state_func = &BasicShot::idle;
    return false;

}
