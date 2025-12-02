#pragma once
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include "gameplay/player/player_manager.hpp"

namespace Game {

class PlayerMoveAction : public IAction {


public:

    PlayerMoveAction(){}

    void reset() override {


    }

    bool execute(Engine::Systems* sys, double dt) override {


        //std::println("cur time = {}", timer.get_time());

        if (sys->player->get_player().pos.vec() == Vector2{ 60, 90 })
            return false;

        return true;

    };

};

}
