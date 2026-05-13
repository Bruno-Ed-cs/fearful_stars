#pragma once

#include "deps.hpp"
#include "gameplay/levels/action.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy.hpp"

namespace Game {

struct WaveEndAction : public Action{

    WaveEndAction() = default;

    bool execute(Engine::Systems& sys, double dt) override {

        if (sys.enemy->no_enemy_left())
            return true;

        return false;

    };

    void restart() override {

    };


};

}
