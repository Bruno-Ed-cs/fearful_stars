#pragma once 
#include "secondary_machine.hpp"


namespace Game {


class MissileShooter : public SecondaryMachine {

public:

    MissileShooter() = default;

    void run(Player& player, Engine::Systems& sys, double dt);

};
}
