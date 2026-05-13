#pragma once
#include "gameplay/levels/action.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy.hpp"

namespace Game {

class SpawnUpgradeAction : public Action {

public:

    uint32_t upgrade_id = 0;

    SpawnUpgradeAction() {}

    void restart() override {  

        upgrade_id = 0;
    }

    bool execute(Engine::GameState& sys, double dt) override {

        if (upgrade_id == 0 ) {

            upgrade_id = sys.projectile->emplace<UpgradeProj>(Vector2{319, 90}, Vector2{-1, 0}, 30, false);

        }

        if (sys.projectile->exists(upgrade_id)) {

            return false;

        } else {

            return true;

        }

    };

};

}
