#include "systems.hpp"

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/player/player_manager.hpp"

#include "deps.hpp"


Engine::Systems::Systems() :
    enemy(std::make_unique<Game::EnemyMan>()),
    projectile(std::make_unique<Game::ProjectileMan>()),
    player(std::make_unique<Game::PlayerMan>()),
    level(std::make_unique<Game::LevelManager>(this)) 
{}



