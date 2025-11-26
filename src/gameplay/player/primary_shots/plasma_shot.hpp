#pragma once 
#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/player/primary_shots/shooting_machine.hpp"
#include "timer.hpp"

namespace Game {

class PlasmaShooter : public ShootingMachine {

public:

    PlasmaShooter() {

        shooting_sound = Engine::AssetMan::get_sound("space-laser");

    }

    void run(Player& player, ProjectileMan& projectile_man, double dt) override;

    bool idle(Player& player, ProjectileMan& projectile_man);
    bool shoot_lv1(Player& player, ProjectileMan& projectile_man);
    bool shoot_lv2(Player& player, ProjectileMan& projectile_man);
    bool shoot_lv3(Player& player, ProjectileMan& projectile_man);

private:

    std::function<bool(PlasmaShooter*, Player&, ProjectileMan&)> state_func = &PlasmaShooter::idle;

    double dt;

    Engine::Timer idle_cooldown;
    Engine::Timer chain_cooldown;
    bool shot = false;

    std::shared_ptr<Sound> shooting_sound;

};

}
