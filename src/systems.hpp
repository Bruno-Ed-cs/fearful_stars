#pragma once 

#include "deps.hpp"

namespace Game {

class EnemyMan;
class ProjectileMan;
class PlayerMan;
class LevelManager;

}


namespace Engine {

class MusicMan;

struct Systems {

    std::unique_ptr<Game::EnemyMan> enemy;
    std::unique_ptr<Game::ProjectileMan> projectile;
    std::unique_ptr<Game::PlayerMan> player;
    std::unique_ptr<Game::LevelManager> level;

    Systems();
};

}
