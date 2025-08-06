#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "loops.hpp"
#include "globals.hpp"

void engine::update_loop(double dt) {

    game::PlayerMan::update(dt);
    game::ProjectileMan::update(dt);


}
