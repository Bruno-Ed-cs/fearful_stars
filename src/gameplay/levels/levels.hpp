#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"

namespace Game {

template<typename T>
using uptr = std::unique_ptr<T> ;

class Level {


public:

    Level(std::string_view name);
    Level(std::string_view, std::vector<IAction*> action_list, std::vector<Engine::AssetMan::Ref> preload_list = {});

    void restart();
    void execute(Engine::Systems& sys, double dt);
    bool finished();

public:

    std::string name;
    std::list<uptr<IAction>> actions;
    std::list<uptr<IAction>>::iterator current_action;
    std::vector<Engine::AssetMan::Ref> preloads;
};

class LevelManager {

public:
    enum struct Mode {
        loop,
        exit
    };

public:

    LevelManager();

    void update(Engine::Systems& sys, double dt);
    void rollback();
    void set_level_mode(Mode mode);
    void load_level(std::string_view file_path);


public:

    uptr<Level> level;
    size_t checkpoint_event = 0;
    bool preloaded = false;
    std::function<void()> end_level;


private:

    void loop_level();
    void exit_level();

};

}

