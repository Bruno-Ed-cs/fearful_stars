#pragma once 

#include "systems.hpp"

namespace Game {

class Player;

class AuxMachine {

public:

    virtual void run(Player& player, Engine::Systems& sys, double dt) = 0;


};

}
