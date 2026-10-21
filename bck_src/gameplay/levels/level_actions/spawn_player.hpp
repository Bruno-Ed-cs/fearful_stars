#pragma once
#include "gameplay/levels/action.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy.hpp"

namespace Game {

class SpawnPlayer : public IAction {

public:


    SpawnPlayer() {}

    void restart() override {    }

    bool execute(Engine::SystemsSystems* sys, double dt) override {

        sys->player->init_player(Vector2{40, 90});

        return true;

    };

};

}
