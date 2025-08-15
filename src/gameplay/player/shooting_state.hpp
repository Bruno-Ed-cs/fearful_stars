#pragma once
#include "deps.hpp"


namespace game {

class Player;
class ShootingMachine;

class ShootingState {

    public:

    virtual void run(Player* player, ShootingMachine& machine) = 0;
    virtual ~ShootingState() = default;
    virtual bool is_final() = 0;

};

class StateIdle : public ShootingState {

    public:

    void run(Player* player, ShootingMachine& machine) override;
    bool is_final() override {

        return false;
    }

};

class StateShoot : public ShootingState {

    public:
    void run(Player* player, ShootingMachine& machine) override;
    bool is_final() override {

        return true;
    }

};


}
