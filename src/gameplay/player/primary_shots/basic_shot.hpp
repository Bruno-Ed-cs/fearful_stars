#pragma once
#include "deps.hpp"

#include "gameplay/player/primary_shots/shooting_machine.hpp"
#include "timer.hpp"

namespace Game {

class Player;
class ProjectileMan;

class BasicShooter : public ShootingMachine {

public:

    BasicShooter() = default;

    ~BasicShooter() = default;
    BasicShooter(const ShootingMachine&) = delete;
    BasicShooter& operator=(const ShootingMachine&) = delete;

    void run(Player& player, ProjectileMan& projectile_man, double dt) override;

    bool idle(Player& player, ProjectileMan& projectile_man);
    bool shoot(Player& player, ProjectileMan& projectile_man);
    std::string get_name() override { return "BasicShooter"; };
private:

    std::function<bool(BasicShooter*, Player&, ProjectileMan&)> state_func = &BasicShooter::idle;
    bool m_running = false;

};

}
