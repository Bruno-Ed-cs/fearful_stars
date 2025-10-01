#pragma once
#include "deps.hpp"

#include "shooting_state.hpp"
#include "timer.hpp"

namespace Game {

class Player;
class ProjectileMan;

class ShootingMachine {

public:

    ShootingMachine() {

        m_state_collection["Idle"] = std::make_unique<StateIdle>();
        m_state_collection["Shoot"] = std::make_unique<StateShoot>();

        m_state = "Idle";

    }

    ~ShootingMachine() = default;
    ShootingMachine(const ShootingMachine&) = delete;
    ShootingMachine& operator=(const ShootingMachine&) = delete;


    void run(Player* player, ProjectileMan& projectile_man);
    void transition_to(const std::string& state_name);

private:

    std::string m_state;
    std::string m_initial_state{"Idle"};
    bool m_running;

    std::map<std::string, std::unique_ptr<ShootingState>> m_state_collection;


};
}
