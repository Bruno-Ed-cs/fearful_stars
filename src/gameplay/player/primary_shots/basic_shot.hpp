#pragma once
#include "deps.hpp"

#include "gameplay/player/primary_shots/shooting_machine.hpp"
#include "timer.hpp"

namespace Game {

class Player;
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

class BasicShot : public ShootingMachine {

public:

    BasicShot() {

        m_state_collection["Idle"] = std::make_unique<StateIdle>();
        m_state_collection["Shoot"] = std::make_unique<StateShoot>();

        m_state = "Idle";

    }

    ~BasicShot() = default;
    BasicShot(const ShootingMachine&) = delete;
    BasicShot& operator=(const ShootingMachine&) = delete;


    void run(Player* player, ProjectileMan& projectile_man);
    void transition_to(const std::string& state_name);

private:

    std::string m_state;
    std::string m_initial_state{"Idle"};
    bool m_running;

    std::map<std::string, std::unique_ptr<ShootingState>> m_state_collection;


};

}
