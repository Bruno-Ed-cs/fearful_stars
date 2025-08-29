#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "loops.hpp"
#include "globals.hpp"

void Engine::update_loop(double dt) {

    Game::PlayerMan::update(dt);
    Game::ProjectileMan::update(dt);


}
