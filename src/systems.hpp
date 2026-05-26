#pragma once 

#include "deps.hpp"
#include "rocksdb/db.h"

namespace Game {

class EnemyMan;
class ProjectileMan;
class PlayerMan;
class LevelMan;
struct UiMan;

}

template<typename T>
using uptr = std::unique_ptr<T>;

namespace Engine {

enum struct Mode {

    gameplay,
    main_menu,
    level_select,
    level_editor
};


struct GameState {

    uptr<Game::EnemyMan> enemy;
    uptr<Game::ProjectileMan> projectile;
    uptr<Game::PlayerMan> player;
    uptr<Game::LevelMan> level;
    uptr<Game::UiMan> ui;

    Mode& app_state;    

    //0 means no save loaded
    std::uint32_t save_slot = 0;
    uptr<rocksdb::DB> save_connection;
    
    bool pause = false;

    GameState(Mode& app_state);
    void load(std::string level_path);
    void save_state();
    void load_state();
};

void start_gameplay(Mode& sys_mode, GameState& sys);
void resume_gameplay(Mode& sys_mode);
void go_to_main_menu(Mode& sys_mode);
void go_to_level_editor(Mode& sys_mode);
void go_to_level_select(Mode& sys_mode);

}
