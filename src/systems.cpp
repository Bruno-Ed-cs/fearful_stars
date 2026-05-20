#include "systems.hpp"

#include "gameplay/enemy/enemy.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "render_man.hpp"
#include "gameplay/ui/interfaces/gameplay_ui.hpp"
#include "saving.hpp"

Engine::GameState::GameState(Engine::Mode& app_state) :
    enemy       (std::make_unique<Game::EnemyMan>()),
    projectile  (std::make_unique<Game::ProjectileMan>()),
    player      (std::make_unique<Game::PlayerMan>()),
    level       (std::make_unique<Game::LevelManager>()),
    ui          (std::make_unique<Game::UiMan>(RenderMan::canva_size())),
    app_state   (app_state)
{
    player->init_player({60, 90});
}


void Engine::GameState::load(std::string level_path) {
    enemy.reset(new Game::EnemyMan());
    projectile.reset(new Game::ProjectileMan());
    player.reset(new Game::PlayerMan());
    ui.reset(new Game::UiMan(RenderMan::canva_size()));
    
    save_slot = 1;
    save_connection = get_save_db(save_slot);

    level->load_level(level_path);
    player->init_player({60, 90});
    ui->stack_interface(std::make_unique<Game::GameplayUi>());
}
