#pragma once
#include "deps.hpp"


namespace game {

class Player;
class ShootingMachine;

class ShootingState {

    public:

    virtual void run(Player* player, ShootingMachine& machine) = 0;
    virtual ~ShootingState() = default;

};

class StateIdle : public ShootingState {

    public:

    void run(Player* player, ShootingMachine& machine) override;

};

class StateShoot : public ShootingState {

    public:
    void run(Player* player, ShootingMachine& machine) override;


};

}
