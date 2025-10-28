#pragma once
#include "deps.hpp"

namespace Game {

class Player;
class ProjectileMan;

class ShootingMachine {

public:


    virtual void run(Player* player, ProjectileMan& projectile_man) = 0;
    virtual void transition_to(const std::string& state_name) = 0;

};
}
