#pragma once

#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"

namespace Game {

class LevelEvent {

    using subevent_ptr = std::unique_ptr<IAction>;

public:

    LevelEvent(std::string name) :
    name(name) {}

    bool is_done();
    IAction& get_current_subevent();
    void next_action();
    void reset();
    void add_action(IAction* action);

public:

    std::vector<subevent_ptr> action_list;
    size_t action_index = 0;
    std::string name;


};

class LevelManager {

public:
    enum struct LevelMode {
        loop,
        exit
    };

public:

    LevelManager(Engine::Systems* sys) :
    systems(sys) {


        end_level = std::bind(&LevelManager::loop_level, &*this);
    };

    void update(double dt);
    void rollback();
    void next_event();
    void add_event(LevelEvent* event);
    void set_level_mode(LevelMode mode);


public:
    std::vector<std::unique_ptr<LevelEvent>> level;
    size_t current_event = 0;
    size_t checkpoint_event = 0;

    Engine::Systems* systems;
    std::function<void()> end_level;


private:

    void loop_level();
    void exit_level();

};

}

