#pragma once

#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include "gameplay/enemy/enemy_man.hpp"

namespace Game {

struct WaveEndAction : public IAction{

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
