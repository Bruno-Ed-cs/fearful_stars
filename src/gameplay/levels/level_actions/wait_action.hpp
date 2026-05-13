#pragma once
#include "gameplay/levels/action.hpp"
#include "systems.hpp"
#include "timer.hpp"

namespace Game {

class WaitAction : public Action {

    Engine::Timer timer;

public:

    WaitAction(double seconds) :
    timer(seconds) {}

    void restart() override {

        timer.reset();
    }

    bool execute(Engine::GameState& sys, double dt) override {

        timer.update(dt);

        //std::println("cur time = {}", timer.get_time());

        if (timer.past_limit())
            return true;

        return false;

    };

};

}
