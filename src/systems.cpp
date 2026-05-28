#include "systems.hpp"

#include "background_man.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "render_man.hpp"
#include "gameplay/ui/interfaces/gameplay_ui.hpp"
#include "rocksdb/options.h"
#include "rocksdb/status.h"
#include "saving.hpp"
#include <system_error>

Engine::GameState::GameState(size_t save_slot) :
    enemy       (std::make_unique<Game::EnemyMan>()),
    projectile  (std::make_unique<Game::ProjectileMan>()),
    player      (std::make_unique<Game::PlayerMan>()),
    level       (std::make_unique<Game::LevelMan>()),
    ui          (std::make_unique<Game::UiMan>(RenderMan::canva_size())),
    save_slot   (save_slot)
{

    if (save_slot != 0) {

        save_connection = get_save_db(save_slot);
    }

    player->init_player({60, 90});
}


void Engine::GameState::load(std::string level_path) {
    enemy.reset(new Game::EnemyMan());
    projectile.reset(new Game::ProjectileMan());
    player.reset(new Game::PlayerMan());
    ui.reset(new Game::UiMan(RenderMan::canva_size()));
    

    level->load_level_file(level_path);

    player->init_player({60, 90});
    ui->stack_interface(std::make_unique<Game::GameplayUi>());



}

void Engine::GameState::save_state() {
    if (save_slot == 0) return;


    player->save_player(*this);
    projectile->save_projectiles(*this);
    enemy->save_enemies(*this);
    level->save_level(*this);
    Engine::BackgroundMan::save_background(*this);
    std::println("saving ......");

    rocksdb::Status result;
    result = save_connection->Put(rocksdb::WriteOptions(), "Database:empty", "0");

    if (!result.ok()) {
        std::cerr << result.ToString() << std::endl;
    }
}

void Engine::GameState::load_state() {
    if (save_slot == 0) return;

    rocksdb::Status result;
    std::string value;
    result = save_connection->Get(rocksdb::ReadOptions(),"Database:empty", &value);

    if (result.IsNotFound()) {
        std::cerr << "Tried to load empty save" << std::endl;
        return;

    } else if (!result.ok()) {

        std::cerr << result.ToString() << std::endl;
    }

    player->load_player(*this);
    projectile->load_projectiles(*this);
    enemy->load_enemies(*this);
    level->load_level(*this);
    Engine::BackgroundMan::load_background(*this);
    std::println("loading player....");
}
