#pragma once
#include "gameplay/levels/i_action.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy_man.hpp"

namespace Game {

class SpawnPlayer : public IAction {

    std::vector<std::tuple<std::string, Vector2>> spawn_targets;

public:

    uint32_t upgrade_id = 0;

    SpawnPlayer() {}

    void reset() override {    }

    bool execute(Engine::Systems* sys, double dt) override {

        sys->player->init_player(Vector2{40, 90});

        return true;

    };

};

}
