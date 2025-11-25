#pragma once
#include "deps.hpp"

#include "gameplay/player/primary_shots/shooting_machine.hpp"
#include "timer.hpp"

namespace Game {

class Player;
class ProjectileMan;

class BasicShot : public ShootingMachine {

public:

    BasicShot() = default;

    ~BasicShot() = default;
    BasicShot(const ShootingMachine&) = delete;
    BasicShot& operator=(const ShootingMachine&) = delete;

    void run(Player& player, ProjectileMan& projectile_man, double dt) override;

    bool idle(Player& player, ProjectileMan& projectile_man);
    bool shoot(Player& player, ProjectileMan& projectile_man);

private:

    std::function<bool(BasicShot*, Player&, ProjectileMan&)> state_func = &BasicShot::idle;
    bool m_running = false;

};

}
