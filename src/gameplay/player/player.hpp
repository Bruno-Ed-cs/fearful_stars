#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "i_entity.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include "shooting_machine.hpp"
#include "component.hpp"
#include "input_man.hpp"
#include "globals.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "shooting_machine.hpp"

namespace Game {

class ProjectileMan;
class EnemyMan;

class Player : public Engine::IEntity{

public:

    Player() {

        shooting_sound = Engine::AssetMan::get_sound("space-laser");
        spritesheet = Engine::AssetMan::get_texture("Space_VH");
    }

    Player(Vector2 pos) {

        this->pos = pos;
        shooting_sound = Engine::AssetMan::get_sound("space-laser");
        spritesheet = Engine::AssetMan::get_texture("Space_VH");

    }

    void update(double dt, Engine::Systems& sys) override; 
    void draw() override;
    Engine::ComponentContainer get_components() override;

public:

    double speed = 145.0f;
    Engine::Timer cooldown = Engine::Timer(0.5f);
    ShootingMachine shooting_machine;
    std::shared_ptr<Sound> shooting_sound;
    std::shared_ptr<Texture> spritesheet;

    Position pos = Position(0.0, 0.0);
    Direction dir = Direction(0.0, 0.0);
    Hitbox hitbox = Hitbox(10.0f, 10.0f);
    Health hp = Health(3);

private:
};

}
