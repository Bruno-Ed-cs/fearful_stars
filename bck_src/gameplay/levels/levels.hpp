#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/levels/action.hpp"
#include "systems.hpp"
#include <string_view>

namespace Game {

    template<typename T>
        using uptr = std::unique_ptr<T> ;

    class Level {


        public:

            Level(std::string_view name, std::string_view path);
            Level(std::string_view, std::string_view path, std::vector<Action*> action_list, std::vector<Engine::AssetMan::Ref> preload_list = {});

            void restart();
            void execute(Engine::GameState& sys, double dt);
            bool finished();

        public:

            std::string name;
            std::string path;
            std::list<uptr<Action>> actions;
            std::list<uptr<Action>>::iterator current_action;
            std::vector<Engine::AssetMan::Ref> preloads;
    };

    class LevelMan {

        public:
            enum struct Mode {
                loop,
                exit
            };

        public:

            LevelMan();

            void update(Engine::GameState& sys, double dt);
            void rollback();
            void set_level_mode(Mode mode);
            void load_level_file(std::string_view file_path);

            void save_level(Engine::GameState& sys);
            void load_level(Engine::GameState& sys);


        public:

            uptr<Level> level;
            size_t checkpoint_event = 0;
            bool preloaded = false;
            std::function<void()> end_level;
            Mode mode;


        private:

            void loop_level();
            void exit_level();

    };

}

