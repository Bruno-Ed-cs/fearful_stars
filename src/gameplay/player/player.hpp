#pragma once

#include "asset_man.hpp"
#include "container.hpp"
#include "deps.hpp"

#include "gameplay/player/aux_powers/aux_machine.hpp"
#include "gameplay/player/aux_powers/orbital_shield.hpp"
#include "gameplay/player/primary_shots/plasma_shot.hpp"
#include "gameplay/player/secondary_shots/missile_shooter.hpp"
#include "gameplay/player/secondary_shots/secondary_machine.hpp"
#include "gameplay/player/special_shots/big_shooter.hpp"
#include "gameplay/player/special_shots/special_machine.hpp"
#include "entity.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include "gameplay/components.hpp"
#include "gameplay/player/primary_shots/basic_shot.hpp"
#include <memory>


namespace Game {

class ProjectileMan;
class EnemyMan;

class Player : public Engine::Entity{

    template<typename T>
    using uptr = std::unique_ptr<T>;

    template<typename T>
    using sptr = std::shared_ptr<T>;

public:

    Player() {

        //primary_shot = std::make_unique<PlasmaShooter>();
        //secondary_shot = std::make_unique<MissileShooter>();
        //special_shot = std::make_unique<BigShooter>();
        //aux_power = std::make_unique<OrbitalShield>();
        Engine::RenderMan::make_outline(*spritesheet, BLUE);

    }

    Player(Vector2 pos) {

        Containers::position[this->pos] = pos;
//        primary_shot = std::make_unique<PlasmaShooter>();
 //       secondary_shot = std::make_unique<MissileShooter>();
 //       special_shot = std::make_unique<BigShooter>();
 //       aux_power = std::make_unique<OrbitalShield>();
        Engine::RenderMan::make_outline(*spritesheet, BLUE);
    }

    void update(double dt, Engine::Systems& sys) override; 
    void draw() override;
    void turn_invincible(double seconds);
    Rectangle get_hitbox() { 
        Rectangle copy = Containers::hitbox[this->hitbox].get(Containers::position[this->pos]);
        return copy;
    };
    void die(Engine::Systems& sys);
    void revive();
    bool destroy_self() override { return self_destruct; };
    void take_damage();

    ~Player() {

        Containers::cleanup_by_owner(this->self_index);
    };

public:

    double speed = 135.0f;
    int special_meter = 0;
    int upgrade = 0;

    Engine::Timer cooldown = Engine::Timer(0.5f);
    Engine::Timer graze_cooldown = Engine::Timer(0.10);

//    uptr<ShootingMachine> primary_shot;
//    int primary_level = 1;
//
//    uptr<SecondaryMachine> secondary_shot;
//    int secondary_level = 0;
//
//    uptr<SpecialMachine> special_shot;
//
//    uptr<AuxMachine> aux_power;
//    int aux_level = 0;
    
    sptr<Sound> shooting_sound =Engine::AssetMan::get_sound("space-laser");
    sptr<Texture> spritesheet = Engine::AssetMan::get_texture("player_ship");

    size_t pos = Containers::position.insert(Position(0.0, 0.0), &self_index);
    size_t dir = Containers::direction.insert(Direction(0.0, 0.0), &self_index);
    size_t hitbox = Containers::hitbox.insert(Hitbox(2.0f, 2.0f), &self_index);
    size_t lives = Containers::health.insert(Health(5), &self_index);
    size_t tag = Containers::player_tag.insert(PlayerTag(), &self_index);

    Hitbox graze_range = Hitbox(42, 30);

    bool dead = false;
    bool invincible = false;
    Engine::Timer invis_timer;

    bool self_destruct = false;

};

}
