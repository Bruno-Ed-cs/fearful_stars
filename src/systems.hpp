#pragma once 

#include "deps.hpp"

namespace Game {

class EnemyMan;
class ProjectileMan;
class PlayerMan;
class LevelManager;
struct UiMan;

}

template<typename T>
using uptr = std::unique_ptr<T>;

namespace Engine {


struct GameState {

    uptr<Game::EnemyMan> enemy;
    uptr<Game::ProjectileMan> projectile;
    uptr<Game::PlayerMan> player;
    uptr<Game::LevelManager> level;
    uptr<Game::UiMan> ui;
    
    bool pause = false;

    GameState(std::string level_path);
};

}
