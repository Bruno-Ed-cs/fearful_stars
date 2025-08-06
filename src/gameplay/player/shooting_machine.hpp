#pragma once
#include "deps.hpp"

#include "shooting_state.hpp"

namespace game {

class Player;

class ShootingMachine {

public:

    ShootingMachine() {

        m_state_collection["Idle"] = std::make_unique<StateIdle>();
        m_state_collection["Shoot"] = std::make_unique<StateShoot>();

        m_state = m_state_collection["Idle"].get();

    }

    ~ShootingMachine() = default;


    void run(Player* player);
    void transition_to(const std::string state_name);

private:

    ShootingState* m_state;

    std::map<std::string, std::unique_ptr<ShootingState>> m_state_collection;


};
}
