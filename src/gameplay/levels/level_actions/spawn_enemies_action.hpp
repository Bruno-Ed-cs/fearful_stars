#pragma once
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy_man.hpp"

namespace Game {

class SpawnEnemiesAction : public IAction {

    std::vector<std::tuple<std::string, Vector2>> spawn_targets;

public:

    SpawnEnemiesAction(std::initializer_list<std::tuple<std::string, Vector2>> targets) :
    spawn_targets(std::move(targets)) {}

    void reset() override {    }

    bool execute(Engine::Systems* sys, double dt) override {

        for (auto spawn_target : spawn_targets) {

            sys->enemy->emplace_enemy(std::get<std::string>(spawn_target), std::get<Vector2>(spawn_target));

        }

        return true;

    };

};

}
