#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "timer.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "systems.hpp"

namespace Game {

class MissileProj : public Projectile {

public:

    MissileProj() 
    {

        sprite = Engine::AssetMan::get_texture("missile");

    }

    MissileProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {

        sprite = Engine::AssetMan::get_texture("missile");

    }

    bool is_foe() { return foe; }
    Rectangle get_hitbox() { return hitbox.get(pos); }
    Vector2 get_position() { return pos.vec(); }
    double get_speed() { return speed; }
    ProjectileType get_type() { return ProjectileType::Missile; }
    bool destroy_self() { return destruct; }
    int get_damage() { return damage; }

    void update(double dt, Engine::GameState& sys);
    void draw();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0);

   Package package() override {
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

   void unpack(Package packed_mem) override {

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
    Hitbox hitbox = Hitbox(6, 3);
    int damage = 1;
    double speed = 200;
    bool foe = false;
    bool destruct = false;
    Hitbox search_area = Hitbox(100, 70);
    Engine::Timer dorment_time = Engine::Timer(0.25f);

    std::shared_ptr<Texture> sprite;

};

}
