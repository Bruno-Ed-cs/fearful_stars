#pragma once
#include "gameplay/levels/action.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy.hpp"

namespace Game {

class WaitUpgradeAction : public Action {

public:


    WaitUpgradeAction() {}

    void restart() override {  

    }

    bool execute(Engine::GameState& sys, double dt) override {
        if (sys.projectile->contains_type(ProjectileType::Upgrade)) {
            return false;
        } else {
            return true;
        }
    };

};

}
