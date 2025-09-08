#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "loops.hpp"
#include "globals.hpp"

void Engine::update_loop(double dt, Game::EnemyMan& enemy_man, Game::ProjectileMan& projectile_man) {

    Game::PlayerMan::update(dt, enemy_man, projectile_man);
    projectile_man.update(dt, enemy_man);
    enemy_man.update(dt, projectile_man);


}
