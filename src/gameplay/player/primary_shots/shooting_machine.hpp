#pragma once
#include "deps.hpp"

namespace Game {

class Player;
class ProjectileMan;

class ShootingMachine {

public:

    virtual void run(Player& player, ProjectileMan& projectile_man, double dt) = 0;

};
}
