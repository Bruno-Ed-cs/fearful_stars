#pragma once

#include "asset_man.hpp"
#include "component.hpp"
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

    Player(ComponentMan& components):
    Engine::Entity(components){

        //primary_shot = std::make_unique<PlasmaShooter>();
        //secondary_shot = std::make_unique<MissileShooter>();
        //special_shot = std::make_unique<BigShooter>();
        //aux_power = std::make_unique<OrbitalShield>();
        Engine::RenderMan::make_outline(*spritesheet, PURPLE);

    }

    Player(ComponentMan& components, Vector2 pos):
    Engine::Entity(components){

        comp.position[this->pos] = pos;
//        primary_shot = std::make_unique<PlasmaShooter>();
 //       secondary_shot = std::make_unique<MissileShooter>();
 //       special_shot = std::make_unique<BigShooter>();
 //       aux_power = std::make_unique<OrbitalShield>();
        Engine::RenderMan::make_outline(*spritesheet, PURPLE);
    }

    void update(double dt, Engine::Systems& sys) override; 
    void draw(Engine::Systems& sys) override;
    void turn_invincible(double seconds);
    Rectangle get_hitbox(Engine::Systems& sys) { 
        Rectangle copy = comp.hitbox[this->hitbox].get(comp.position[this->pos]);
        return copy;
    };
    void die(Engine::Systems& sys);
    void revive(Engine::Systems& sys);
    bool destroy_self() override { return self_destruct; };
    void take_damage(Engine::Systems& sys);

    ~Player() {

    };

public:

    int special_meter = 0;
    int upgrade = 0;

    size_t cooldown =       comp.timer.insert(Timer(0.5f), &self_index);
    size_t graze_cooldown = comp.timer.insert(Timer(0.10f), &self_index);

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
    
    sptr<Sound> shooting_sound = Engine::AssetMan::get_sound("space-laser");
    sptr<Texture> spritesheet = Engine::AssetMan::get_texture("player_ship");

    size_t speed = comp.speed.insert(Speed(135.0f), &self_index);
    size_t pos = comp.position.insert(Position(0.0, 0.0), &self_index);
    size_t dir = comp.direction.insert(Direction(0.0, 0.0), &self_index);
    size_t hitbox = comp.hitbox.insert(Hitbox(2.0f, 2.0f, pos), &self_index);
    size_t lives = comp.health.insert(Health(10), &self_index);
    size_t tag = comp.player_tag.insert(PlayerTag(), &self_index);

    Hitbox graze_range = Hitbox(42, 30);

    bool dead = false;
    bool invincible = false;
    Engine::Timer invis_timer;

    bool self_destruct = false;

};

}
