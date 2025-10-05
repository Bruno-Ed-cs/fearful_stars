#pragma once
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include "timer.hpp"

namespace Engine {

class WaitAction : public IAction {

    Engine::Timer timer;

public:

    WaitAction(double seconds) :
    timer(seconds) {}

    void reset() override {

        timer.reset();

    }

    bool execute(Systems* sys, double dt) override {

        timer.update(dt);

        //std::println("cur time = {}", timer.get_time());

        if (timer.past_limit())
            return true;

        return false;

    };

};

}
