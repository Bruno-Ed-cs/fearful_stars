#pragma once
#include "deps.hpp"


namespace Game {

class Player;
class ShootingMachine;
class ProjectileMan;

class ShootingState {

    public:

    virtual void run(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) = 0;
    virtual bool transition(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) = 0;
    virtual ~ShootingState() = default;
    virtual bool is_final() = 0;

};

class StateIdle : public ShootingState {

    public:
    bool transition(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) override;
    void run(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) override;
    bool is_final() override {

        return false;
    }

};

class StateShoot : public ShootingState {

    public:
    bool transition(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) override;
    void run(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) override;
    bool is_final() override {

        return true;
    }

};


}
