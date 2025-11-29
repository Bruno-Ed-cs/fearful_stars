#pragma once 
#include "secondary_machine.hpp"
#include "timer.hpp"


namespace Game {


class MissileShooter : public SecondaryMachine {

public:

    MissileShooter() = default;

    void run(Player& player, Engine::Systems& sys, double dt);

    Engine::Timer cooldown = Engine::Timer(0.60f);

};
}
