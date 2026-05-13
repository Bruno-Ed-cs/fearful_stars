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
    const std::type_info& get_type() { return typeid(MissileProj); }
    bool destroy_self() { return destruct; }
    int get_damage() { return damage; }

    void update(double dt, Engine::GameState& sys);
    void draw();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0);

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
