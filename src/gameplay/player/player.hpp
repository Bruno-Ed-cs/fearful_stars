#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/player/aux_powers/aux_machine.hpp"
#include "gameplay/player/secondary_shots/secondary_machine.hpp"
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
        primary_shot = std::make_unique<BasicShot>();
    }

    Player(Vector2 pos) {

        this->pos = pos;
        shooting_sound = Engine::AssetMan::get_sound("space-laser");
        spritesheet = Engine::AssetMan::get_texture("player");
        primary_shot = std::make_unique<BasicShot>();
    }

    void update(double dt, Engine::Systems& sys) override; 
    void draw() override;
    Engine::ComponentContainer get_components() override;
    bool destroy_self() override { return self_destruct; };

public:

    double speed = 135.0f;
    int special_meter = 0;

    Engine::Timer cooldown = Engine::Timer(0.5f);
    Engine::Timer graze_cooldown = Engine::Timer(0.10);

    uptr<ShootingMachine> primary_shot;
    uptr<SecondaryMachine> secondary_shot;
    uptr<SpecialMachine> special_shot;
    uptr<AuxMachine> aux_power;
    
    sptr<Sound> shooting_sound;
    sptr<Texture> spritesheet;

    Position pos = Position(0.0, 0.0);
    Direction dir = Direction(0.0, 0.0);
    Hitbox hitbox = Hitbox(4.0f, 4.0f);
    Hitbox graze_range = Hitbox(28, 18);
    Health hp = Health(3);

    bool self_destruct = false;

};

}
