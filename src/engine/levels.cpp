#include "levels.hpp"
#include "systems.hpp"

using namespace Engine;

void LevelManager::loop_level() {

    current_event = 0;
    checkpoint_event = 0; 

    level[current_event]->reset();

}

void LevelManager::exit_level() {

}

void LevelManager::add_event(LevelEvent* event) {

    level.emplace_back(event);

}

void LevelManager::update(double dt) {

    if (level.empty())
        return;

    if (level.size() <= current_event) {

        end_level();
    }

    auto& curr_action = level[current_event]->get_current_subevent();

    if (curr_action.execute(systems, dt)) {
        level[current_event]->next_action();
    }

    if (level[current_event]->is_done()) {
        next_event();
    }
}

void LevelManager::next_event() {
    ++current_event;
}

void LevelManager::rollback() {
    if (checkpoint_event < level.size()) {
        current_event = checkpoint_event;
    } else {
        current_event = 0;   
    }
}


bool LevelEvent::is_done() {

    if (action_index >= action_list.size()) 
        return true;

    return false;

}

IAction& LevelEvent::get_current_subevent() {

    if (!is_done()) {

        return *action_list[action_index];
    }

    throw (std::range_error("Current action is out of bounds for the event"));

}

void LevelEvent::next_action() {

    if (!is_done()) {

        ++action_index;
    }

}

void LevelEvent::reset() {

    action_index = 0;

    for (auto& action : action_list) {

        action->reset();
    }

}

void LevelEvent::add_action(IAction* action) {

    action_list.emplace_back(action);

}
