#pragma once

#include "systems.hpp"
#include "special_machine.hpp"

namespace Game {

class Player;

class BigShooter : public SpecialMachine {

public:

    void run(Player& player, Engine::GameState& sys, double dt);


};

}
