#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/player/aux_powers/aux_machine.hpp"
#include "gameplay/player/aux_powers/orbital_shield.hpp"
#include "gameplay/player/primary_shots/plasma_shot.hpp"
#include "gameplay/player/secondary_shots/missile_shooter.hpp"
#include "gameplay/player/secondary_shots/secondary_machine.hpp"
#include "gameplay/player/special_shots/big_shooter.hpp"
#include "gameplay/player/special_shots/special_machine.hpp"
#include "i_entity.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include "component.hpp"
#include "input_man.hpp"
#include "globals.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/player/primary_shots/basic_shot.hpp"

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include <memory>


namespace Game {

class ProjectileMan;
class EnemyMan;

class Player : public Engine::IEntity{

    template<typename T>
    using uptr = std::unique_ptr<T>;

    template<typename T>
    using sptr = std::shared_ptr<T>;

public:

    Player() {

        shooting_sound = Engine::AssetMan::get_sound("space-laser");
        spritesheet = Engine::AssetMan::get_texture("player");
        primary_shot = std::make_unique<PlasmaShooter>();
        secondary_shot = std::make_unique<MissileShooter>();
        special_shot = std::make_unique<BigShooter>();
        aux_power = std::make_unique<OrbitalShield>();
    }

    Player(Vector2 pos) {

        this->pos = pos;
        shooting_sound = Engine::AssetMan::get_sound("space-laser");
        spritesheet = Engine::AssetMan::get_texture("player");
        primary_shot = std::make_unique<PlasmaShooter>();
        secondary_shot = std::make_unique<MissileShooter>();
        special_shot = std::make_unique<BigShooter>();
        aux_power = std::make_unique<OrbitalShield>();
    }

    void update(double dt, Engine::Systems& sys) override; 
    void draw() override;
    void turn_invincible(double seconds);
    void die(Engine::Systems& sys);
    void revive();
    bool destroy_self() override { return self_destruct; };

public:

    double speed = 135.0f;
    int special_meter = 0;

    Engine::Timer cooldown = Engine::Timer(0.5f);
    Engine::Timer graze_cooldown = Engine::Timer(0.10);

    uptr<ShootingMachine> primary_shot;
    int primary_level = 1;

    uptr<SecondaryMachine> secondary_shot;
    int secondary_level = 0;

    uptr<SpecialMachine> special_shot;

    uptr<AuxMachine> aux_power;
    int aux_level = 0;
    
    sptr<Sound> shooting_sound;
    sptr<Texture> spritesheet;

    Position pos = Position(0.0, 0.0);
    Direction dir = Direction(0.0, 0.0);
    Hitbox hitbox = Hitbox(2.0f, 2.0f);
    Hitbox graze_range = Hitbox(32, 20);
    Health lives = Health(5);

    bool dead = false;
    bool invincible = false;
    Engine::Timer invis_timer;

    bool self_destruct = false;

};

}
