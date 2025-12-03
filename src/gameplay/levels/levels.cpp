#include "levels.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "asset_man.hpp"

using namespace Game;

void LevelManager::loop_level() {

    level->event_index = 0;
    checkpoint_event = 0; 

    level->reset();

}

void LevelManager::exit_level() {

    Engine::g_running = false;

    Engine::AssetMan::cleanup();
}

void LevelManager::update(double dt) {

    if (level->events.empty())
        return;


//    std::println("curent event = {}", level->event_index);
 //   std::println("current_action = {}", level->curr_event().action_index);

    auto& curr_action = level->curr_action();

    if (curr_action.execute(systems, dt)) {

        level->curr_event().next();

        if (level->curr_event().at_end()) {

            if (level->at_end()) {
                end_level();
            }
        }

    }

}


void LevelManager::rollback() {
    if (checkpoint_event < level->events.size()) {
        level->event_index = checkpoint_event;
    } else {
        level->event_index = 0;   
    }
}


bool LevelEvent::at_end() {

    if (cur_action == actions.end()) 
        return true;

    return false;

}

IAction& LevelEvent::current_action() {

    if (at_end()) {

        throw (std::range_error("Current action is out of bounds for the event"));
    }

    return **cur_action;
}

void LevelEvent::next() {

    ++cur_action;

}

void LevelEvent::reset() {

    if (at_end()) 
        --cur_action;


    do {

        cur_action->reset();

    } while (cur_action != actions.begin());
}

void LevelEvent::add_action(IAction* action) {

    actions.emplace_back(action);
    cur_action = actions.begin();

}

void Level::reset() {

    event_index = 0;

    for (auto& event : events) {

        event->reset();

    }

}



LevelEvent& Level::curr_event() {
    if (events.empty() || event_index >= events.size()) {
        throw std::out_of_range("No current event available");
    }

    return *events[event_index];

}

IAction& Level::curr_action() {

    return this->curr_event().current_action();

}


bool Level::at_end() {

    if (event_index == events.size() -1){ 

        std::println("you win");
        CloseWindow();
        return true;
    }

    return false;

}


void Level::next() {
    if (event_index == events.size() -1) {

        return;
    }

    if (event_index >= events.size()) {

        event_index = events.size() -1;

    } else {

        ++event_index;

    }
}

void Level::add_event(LevelEvent* event) {

    events.emplace_back(event);

}

uptr<Level> Level::make_level(const std::string& name) {

    auto level = std::make_unique<Level>();

    level->name = name;

    return std::move(level);

}

