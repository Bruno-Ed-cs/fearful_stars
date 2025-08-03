#pragma once
#include "deps.hpp"

#include "shooting_state.hpp"

namespace game {

class Player;

class ShootingMachine {

public:

    ShootingMachine() :
    m_state(new StateIdle()) {}

    ~ShootingMachine() {

        delete m_state;

    }

    void run(Player* player);

private:

    ShootingState* m_state;

};
}
