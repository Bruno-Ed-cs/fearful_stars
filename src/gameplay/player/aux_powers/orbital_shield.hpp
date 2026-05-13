#pragma once 

#include "systems.hpp"
#include "aux_machine.hpp"

namespace Game {

class Player;

class OrbitalShield : public AuxMachine {

public:

    void run(Player& player, Engine::GameState& sys, double dt);

    uint32_t orb1 = 0;
    uint32_t orb2 = 0;

};

}
