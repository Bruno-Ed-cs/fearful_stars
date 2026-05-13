#include "systems.hpp"

#include "gameplay/enemy/enemy.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "render_man.hpp"
#include "gameplay/ui/interfaces/gameplay_ui.hpp"

Engine::GameState::GameState(std::string level_path) :
    enemy       (std::make_unique<Game::EnemyMan>()),
    projectile  (std::make_unique<Game::ProjectileMan>()),
    player      (std::make_unique<Game::PlayerMan>()),
    level       (std::make_unique<Game::LevelManager>()),
    ui          (std::make_unique<Game::UiMan>(RenderMan::canva_size()))
{

    level->load_level(level_path);
    player->init_player({60, 90});
    ui->stack_interface(std::make_unique<Game::GameplayUi>());
}



