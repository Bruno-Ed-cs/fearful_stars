#pragma once

#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include <memory>
#include <string_view>

namespace Game {

template<typename T>
using uptr = std::unique_ptr<T> ;

class LevelEvent {

    using subevent_ptr = std::unique_ptr<IAction>;

public:

    LevelEvent(std::string name) :
    name(name) {}

    bool at_end();
    IAction& current_action();
    void next();
    void reset();
    void add_action(IAction* action);

public:

    std::vector<subevent_ptr> action_list;
    size_t action_index = 0;
    std::string name;


};

struct Level{

    size_t event_index = 0;
    std::string name;
    std::vector<uptr<LevelEvent>> events;

    static uptr<Level> make_level(const std::string& name);

    void next();

    LevelEvent& curr_event();

    IAction& curr_action();

    void add_event(LevelEvent* event);

    bool at_end();

    void reset();

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

        end_level = std::bind(&LevelManager::loop_level, this);
    };

    void update(double dt);
    void rollback();
    void set_level_mode(LevelMode mode);


public:

    uptr<Level> level;
    size_t checkpoint_event = 0;
    Engine::Systems* systems;
    std::function<void()> end_level;


private:

    void loop_level();
    void exit_level();

};

}

