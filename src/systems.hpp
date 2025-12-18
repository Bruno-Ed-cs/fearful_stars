#pragma once 

#include "deps.hpp"

namespace Game {

class EnemyMan;
class ProjectileMan;
class PlayerMan;
class LevelManager;
struct UiMan;

}


namespace Engine {

class MusicMan;

struct Systems {

    std::unique_ptr<Game::EnemyMan> enemy;
    std::unique_ptr<Game::ProjectileMan> projectile;
    std::unique_ptr<Game::PlayerMan> player;
    std::unique_ptr<Game::LevelManager> level;
    std::unique_ptr<Game::UiMan> ui;
    
    bool pause = false;

    Systems();
};

}
