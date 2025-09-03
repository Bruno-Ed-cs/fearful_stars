#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "loops.hpp"
#include "globals.hpp"

void Engine::update_loop(double dt, Game::EnemyMan& enemy_man) {

    Game::PlayerMan::update(dt, enemy_man);
    Game::ProjectileMan::update(dt, enemy_man);
    enemy_man.update(dt);


}
