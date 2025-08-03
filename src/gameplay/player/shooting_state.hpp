#pragma once
#include "deps.hpp"


namespace game {

class Player;

class ShootingState {

    public:

    virtual ShootingState* run(Player* player) = 0;
    virtual ~ShootingState() = default;

};

class StateIdle : public ShootingState {

    public:

    ShootingState* run(Player* player) override;

};

class StateShoot : public ShootingState {

    public:
    ShootingState* run(Player* player) override;

};

}
