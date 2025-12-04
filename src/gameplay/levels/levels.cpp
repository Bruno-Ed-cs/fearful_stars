#include "levels.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "asset_man.hpp"
#include <print>

using namespace Game;

Level::Level(std::string_view name) :
name(name), actions(), preloads() {

    current_action = actions.end();
}

Level::Level(std::string_view name, std::initializer_list<IAction*> action_list, std::initializer_list<Engine::AssetMan::Ref> preload_list) :
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

void Level::execute(Engine::Systems& sys, double dt) {

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

void LevelManager::update(Engine::Systems& sys, double dt) {

    if (level == nullptr) {

        return;
        std::println("no level loaded");
    }

    if (!preloaded) {

        preloaded = true;
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

