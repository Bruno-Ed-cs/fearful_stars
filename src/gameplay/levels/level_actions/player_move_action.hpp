#pragma once
#include "gameplay/levels/action.hpp"
#include "systems.hpp"
#include "gameplay/player/player.hpp"

namespace Game {

class PlayerMoveAction : public Action {


public:

    PlayerMoveAction(){}

    void restart() override {


    }

    bool execute(Engine::Systems& sys, double dt) override {


        //std::println("cur time = {}", timer.get_time());

        if (sys.player->get_player().pos.vec() == Vector2{ 60, 90 })
            return false;

        return true;

    };

};

}
