#pragma once

#include "systems.hpp"
namespace Game {

class Player;

class SecondaryMachine {

public:

    virtual void run(Player& player, Engine::GameState& sys, double dt) = 0;

};

}
