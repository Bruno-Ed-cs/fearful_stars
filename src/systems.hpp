#pragma once 

#include "deps.hpp"
#include "gameplay/components.hpp"
#include "entity.hpp"

namespace Game {

class EnemyMan;
class ProjectileMan;
class PlayerMan;
class LevelManager;
struct UiMan;
struct ComponentMan;

}

namespace Engine {

    struct EntityContainer;

}

namespace Engine {

class MusicMan;

struct Systems {

    //std::unique_ptr<Game::EnemyMan> enemy;
    //std::unique_ptr<Game::ProjectileMan> projectile;
    //std::unique_ptr<Game::PlayerMan> player;
    //std::unique_ptr<Game::LevelManager> level;
    std::unique_ptr<Game::UiMan> ui;
    Game::ComponentMan comp;
    Engine::EntityContainer entity;
    
    bool pause = false;

    Vector2 world_size = {.x = 320, .y = 180};
    bool debug = false;
    bool running = true;

    Systems();
};

}
