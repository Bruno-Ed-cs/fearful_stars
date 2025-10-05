#pragma once

#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"

namespace Engine {

struct WaveEndAction : public IAction{

    WaveEndAction() = default;

    bool execute(Systems* sys, double dt) override {

        if (sys->enemy.no_enemy_left())
            return true;

        return false;

    };

    void reset() override {

    };


};

}
