#pragma once
#include "gameplay/levels/action.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy.hpp"

namespace Game {

class SpawnUpgradeAction : public Action {

public:


    SpawnUpgradeAction() {}

    void restart() override {  

    }

    bool execute(Engine::GameState& sys, double dt) override {


         sys.projectile->emplace<UpgradeProj>(Vector2{319, 90}, Vector2{-1, 0}, 30, false);
         return true;

    };

};

}
