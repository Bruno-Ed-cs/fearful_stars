#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "systems.hpp"
#include "timer.hpp"

namespace Game {

class OrbitalProj : public Projectile{

public:

    OrbitalProj() {
        sprite = Engine::AssetMan::get_texture("orbital_proj");

    };

    OrbitalProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {

        sprite = Engine::AssetMan::get_texture("orbital_proj");

    };

    bool is_foe() { return foe; }
    Rectangle get_hitbox() { return hitbox.get(pos); }
    Vector2 get_position() { return pos.vec(); }
    double get_speed() { return speed; }
    const std::type_info& get_type() { return typeid(OrbitalProj); }
    bool destroy_self() { return destruct; }
    int get_damage() { return damage; }

    void update(double dt, Engine::GameState& sys);
    void draw();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0);

public:

//Inicialize as variaveis 

    Position pos;
    Direction orientation;
    Hitbox hitbox = Hitbox(6, 6);
    int damage = 1;
    double speed = 10;
    bool foe;
    bool destruct = false;

    Engine::Timer lifetime = Engine::Timer(10);

    std::shared_ptr<Texture> sprite;

    Position anchor;
    double radius = 12.0;

};

}
