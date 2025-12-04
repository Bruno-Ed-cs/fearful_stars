#pragma once

#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include <memory>
#include <string_view>

namespace Game {

template<typename T>
using uptr = std::unique_ptr<T> ;

class Level {

public:

    Level(std::string_view name);
    Level(std::string_view, std::initializer_list<IAction*> action_list);

    void restart();
    void execute(Engine::Systems& sys, double dt);
    bool finished();

public:

    std::string name;
    std::list<uptr<IAction>> actions;
    std::list<uptr<IAction>>::iterator current_action;

};

class LevelManager {

public:
    enum struct LevelMode {
        loop,
        exit
    };

public:

    LevelManager();

    void update(Engine::Systems& sys, double dt);
    void rollback();
    void set_level_mode(LevelMode mode);


public:

    uptr<Level> level;
    size_t checkpoint_event = 0;
    std::function<void()> end_level;


private:

    void loop_level();
    void exit_level();

};

}

