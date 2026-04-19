#include "systems.hpp"

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "render_man.hpp"


Engine::Systems::Systems() :
    //enemy(std::make_unique<Game::EnemyMan>()),
    //projectile(std::make_unique<Game::ProjectileMan>()),
    //player(std::make_unique<Game::PlayerMan>()),
    //level(std::make_unique<Game::LevelManager>()),
    ui(std::make_unique<Game::UiMan>(RenderMan::canva_size()))
{}



