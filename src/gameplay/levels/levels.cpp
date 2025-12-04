#include "levels.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "asset_man.hpp"
#include <print>

using namespace Game;

Level::Level(std::string_view name) :
name(name), actions() {

    current_action = actions.end();
}

Level::Level(std::string_view, std::initializer_list<IAction*> action_list) :
name(name) {

    for (auto& action: action_list) {

        this->actions.emplace_back(action);
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

        if (action->execute(&sys, dt)) {

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

    level->execute(sys, dt);

    if (level->finished()) {

        end_level();
    }

}

void LevelManager::rollback() {

}

void LevelManager::set_level_mode(LevelMode mode) {

}



void LevelManager::loop_level() {

    level->restart();
}

void LevelManager::exit_level() {

}

