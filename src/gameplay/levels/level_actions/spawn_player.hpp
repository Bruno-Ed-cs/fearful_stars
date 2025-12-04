#pragma once
#include "gameplay/levels/i_action.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy_man.hpp"

namespace Game {

class SpawnPlayer : public IAction {

public:


    SpawnPlayer() {}

    void restart() override {    }

    bool execute(Engine::Systems* sys, double dt) override {

        sys->player->init_player(Vector2{40, 90});

        return true;

    };

};

}
