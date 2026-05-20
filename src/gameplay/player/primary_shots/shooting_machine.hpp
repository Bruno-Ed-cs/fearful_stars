#pragma once
#include "deps.hpp"

namespace Game {

class Player;
class ProjectileMan;

class ShootingMachine {

public:

    virtual void run(Player& player, ProjectileMan& projectile_man, double dt) = 0;
    virtual std::string get_name() = 0;

};

    ShootingMachine* make_shooting_machine(std::string shot_type);
}
