#include "levels.hpp"
#include "systems.hpp"
#include <exception>
#include <stdexcept>

using namespace Game;

void LevelManager::loop_level() {

    level->event_index = 0;
    checkpoint_event = 0; 

    level->reset();

}

void LevelManager::exit_level() {

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
            level->next();

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

    if (action_index == action_list.size() -1) 
        return true;

    return false;

}

IAction& LevelEvent::current_action() {

    if (action_index >= action_list.size()) {

        throw (std::range_error("Current action is out of bounds for the event"));
    }

    return *action_list[action_index];
}

void LevelEvent::next() {

    if (action_index == action_list.size() -1) {

        return;
    }

    if (action_index >= action_list.size()) {

        action_index = action_list.size() -1;

    } else {

        ++action_index;

    }
}

void LevelEvent::reset() {

    action_index = 0;

    for (auto& action : action_list) {

        action->reset();
    }

}

void Level::reset() {

    event_index = 0;

    for (auto& event : events) {

        event->reset();

    }

}

void LevelEvent::add_action(IAction* action) {

    action_list.emplace_back(action);

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

    if (event_index == events.size() -1)
        return true;

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

