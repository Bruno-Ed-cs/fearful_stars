#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "systems.hpp"

namespace Game {

class UpgradeProj : public Projectile{

public:

    UpgradeProj()  {

        sprite = Engine::AssetMan::get_texture("upgrade_proj");

    }
    UpgradeProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {

        sprite = Engine::AssetMan::get_texture("upgrade_proj");

    }

    bool is_foe() override { return foe; }
    Rectangle get_hitbox() override { return hitbox.get(pos); }
    Vector2 get_position() override { return pos.vec(); }
    double get_speed() override { return speed; }
    ProjectileType get_type() override { return ProjectileType::Upgrade; }
    bool destroy_self() override { return destruct; }
    int get_damage() override { return damage; }

    void update(double dt, Engine::GameState& sys) override;
    void draw() override;

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0) override;

    Engine::Package package() override {
       return {
           {"foe", std::to_string(foe)},
           {"pos_x", std::to_string(pos.x)},
           {"pos_y", std::to_string(pos.y)},

           {"orientation_x", std::to_string(orientation.x)},
           {"orientation_y", std::to_string(orientation.y)},

           {"speed", std::to_string(speed)},
           {"damage", std::to_string(damage)},

       };

   }

   void unpack(Engine::Package packed_mem) override {

       foe = std::stoi(packed_mem["foe"]);
       pos.x = std::stod(packed_mem["pos_x"]);
       pos.y = std::stod(packed_mem["pos_y"]);

       orientation.x = std::stod(packed_mem["orientation_x"]);
       orientation.y = std::stod(packed_mem["orientation_y"]);

       speed = std::stod(packed_mem["speed"]);
       damage = std::stoi(packed_mem["damage"]);

   }
public:

//Inicialize as variaveis 

    Position pos;
    Direction orientation;
    Hitbox hitbox = Hitbox(16, 16);
    int damage = 0;
    double speed = 90;
    bool foe = false;
    bool destruct = false;

    std::shared_ptr<Texture> sprite;

};

}
