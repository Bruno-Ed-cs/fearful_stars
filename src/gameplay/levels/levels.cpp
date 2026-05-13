#include "levels.hpp"
#include "gameplay/levels/action.hpp"
#include "gameplay/levels/level_actions/play_ost.hpp"
#include "gameplay/levels/level_actions/player_move_action.hpp"
#include "gameplay/levels/level_actions/spawn_enemies_action.hpp"
#include "gameplay/levels/level_actions/spawn_upgrade_action.hpp"
#include "gameplay/levels/level_actions/wait_action.hpp"
#include "gameplay/levels/level_actions/wave_end_action.hpp"
#include "gameplay/levels/level_actions/set_background_action.hpp"
#include "globals.hpp"
#include "json.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "asset_man.hpp"
#include <memory>
#include <print>

using namespace Game;

Level::Level(std::string_view name) :
name(name), actions(), preloads() {

    current_action = actions.end();
}

Level::Level(std::string_view name, std::vector<Action*> action_list, std::vector<Engine::AssetMan::Ref> preload_list) :
name(name) {

    for (auto& action: action_list) {

        this->actions.emplace_back(action);
    }

    for (auto& asset: preload_list) {

        this->preloads.push_back(asset);

    }

    this->current_action = actions.begin();
}

void Level::restart() {

    for (auto& action: actions) {

        action->restart();

    }

    this->current_action = actions.begin();

}

void Level::execute(Engine::GameState& sys, double dt) {

    if (current_action == actions.end() || actions.empty()) 
        return;

    if (*current_action != nullptr) {

        auto* action = current_action->get();

        if (action->execute(sys, dt)) {

            current_action++;
        }

    } else {

        std::println("the action pointer is null now");
    }

}

bool Level::finished() {

    if (current_action == actions.end())
        return true;

    return false;
}




LevelManager::LevelManager() 
{
    end_level = std::bind(&LevelManager::loop_level, this);
}

void LevelManager::update(Engine::GameState& sys, double dt) {

    if (level == nullptr) {

        return;
        std::println("no level loaded");
    }

    if (!preloaded) {

        preloaded = true;
        std::println("preloading");
        for (auto& asset: level->preloads) {


            switch (asset.type) {

                case Engine::AssetMan::Ref::Type::sprite:
                    Engine::AssetMan::get_texture(asset.name);
                break;

                case Engine::AssetMan::Ref::Type::shader:
                    Engine::AssetMan::get_shader(asset.name);
                break;

                case Engine::AssetMan::Ref::Type::font:
                    Engine::AssetMan::get_font(asset.name);
                break;

                case Engine::AssetMan::Ref::Type::music:
                    Engine::AssetMan::get_music(asset.name);
                break;

                case Engine::AssetMan::Ref::Type::sound:
                    Engine::AssetMan::get_sound(asset.name);
                break;
            
            }

        }

    }

    level->execute(sys, dt);

    if (level->finished()) {

        end_level();
    }

}

void LevelManager::rollback() {

}

void LevelManager::set_level_mode(Mode mode) {

}



void LevelManager::loop_level() {

    level->restart();
}

void LevelManager::exit_level() {

}

using json = nlohmann::json;

void LevelManager::load_level(std::string_view file_path) {

    std::string base_dir(GetApplicationDirectory());
    base_dir += "assets/levels/";
    base_dir += file_path;

    char* source_file = LoadFileText(base_dir.c_str());

    json raw_level = json::parse(source_file);

    UnloadFileText(source_file);

    std::string level_name = raw_level["name"];
    std::vector<Action*> actions;
    std::vector<Engine::AssetMan::Ref> preloads;

    for (auto& action : raw_level["actions"]) {

        if (action["type"] == "SetBackgroundAction") {

            actions.push_back(new SetBackgroundAction(action["bg"]));

        }

        if (action["type"] == "PlayerMoveAction") {

            actions.push_back(new PlayerMoveAction());

        }

        if (action["type"] == "PlayOstAction") {

            actions.push_back(new PlayOstAction(action["track"]));

        }

        if (action["type"] == "SpawnUpgradeAction") {

            actions.push_back(new SpawnUpgradeAction());

        }

        if (action["type"] == "WaitAction") {

            actions.push_back(new WaitAction(action["duration"]));

        }

        if (action["type"] == "WaveEndAction") {

            actions.push_back(new WaveEndAction());

        }

        if (action["type"] == "SpawnEnemiesAction") {
            
            std::vector<std::tuple<std::string, Vector2>> enemy_list;

            for (auto& enemy : action["enemies"]) {

                enemy_list.push_back({enemy["enemy_type"], {enemy["position"][0], enemy["position"][1]}});

            }

            actions.push_back(new SpawnEnemiesAction(enemy_list));

        }

    }

    for (auto& asset : raw_level["assets"]) {

        Engine::AssetMan::Ref::Type asset_type;

        if (asset["type"] == "sprite") {

            asset_type = Engine::AssetMan::Ref::Type::sprite;

        }

        if (asset["type"] == "font") {

            asset_type = Engine::AssetMan::Ref::Type::font;

        }

        if (asset["type"] == "shader") {
            
            asset_type = Engine::AssetMan::Ref::Type::shader;

        }

        if (asset["type"] == "music") {

            asset_type = Engine::AssetMan::Ref::Type::music;

        }

        if (asset["type"] == "sound") {

            asset_type = Engine::AssetMan::Ref::Type::sound;

        }

        preloads.push_back({asset["name"], asset_type});

    }

    this->level = std::make_unique<Level>(level_name, actions, preloads);
}
