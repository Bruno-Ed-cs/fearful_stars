#pragma once 
#include "deps.hpp"
#include "gameplay/player/primary_shots/shooting_machine.hpp"
#include "timer.hpp"

namespace Game {

class PlasmaShooter : public ShootingMachine {

public:

    PlasmaShooter() {}

    void run(Player& player, ProjectileMan& projectile_man, double dt) override;

    bool idle(Player& player, ProjectileMan& projectile_man);
    bool chain_shot(Player& player, ProjectileMan& projectile_man);
    bool shoot(Player& player, ProjectileMan& projectile_man);

private:

    std::function<bool(PlasmaShooter*, Player&, ProjectileMan&)> state_func = &PlasmaShooter::idle;

    Engine::Timer idle_cooldown;
    Engine::Timer chain_cooldown;
};

}
