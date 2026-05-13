#include "systems.hpp"

#include "gameplay/enemy/enemy.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "render_man.hpp"


Engine::Systems::Systems() :
    enemy(std::make_unique<Game::EnemyMan>()),
    projectile(std::make_unique<Game::ProjectileMan>()),
    player(std::make_unique<Game::PlayerMan>()),
    level(std::make_unique<Game::LevelManager>()),
    ui(std::make_unique<Game::UiMan>(RenderMan::canva_size()))
{}



