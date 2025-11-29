#pragma once

#include "systems.hpp"

namespace Game {

class Player;

class SpecialMachine {

public:

    virtual void run(Player& player, Engine::Systems& sys, double dt) = 0;


};

}
