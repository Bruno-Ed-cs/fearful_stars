#pragma once 

#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "levels.hpp"

namespace Engine {

struct Systems {

    Game::EnemyMan enemy;
    Game::ProjectileMan projectile;
    Game::PlayerMan player;
    Engine::LevelManager level;

    Systems() :
    enemy(), projectile(), player(), level(this) {};

};

}
