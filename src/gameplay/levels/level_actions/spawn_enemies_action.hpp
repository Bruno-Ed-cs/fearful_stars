#pragma once
#include "gameplay/levels/action.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy.hpp"

namespace Game {

class SpawnEnemiesAction : public Action {

    std::vector<std::tuple<std::string, Vector2>> spawn_targets;

public:

    SpawnEnemiesAction(std::vector<std::tuple<std::string, Vector2>> targets) :
    spawn_targets(std::move(targets)) {}

    void restart() override {

    }

    bool execute(Engine::GameState& sys, double dt) override {

        for (auto spawn_target : spawn_targets) {

            sys.enemy->emplace_enemy(std::get<std::string>(spawn_target), std::get<Vector2>(spawn_target));

        }

        return true;

    };

};

}
