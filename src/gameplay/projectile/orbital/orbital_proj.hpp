#pragma once

#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "systems.hpp"

namespace Game {

class OrbitalProj : public IProjectile{

public:

    OrbitalProj() = default;
    OrbitalProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {}

    bool is_foe() { return foe; }
    Rectangle get_hitbox() { return hitbox.get(pos); }
    Vector2 get_position() { return pos.vec(); }
    double get_speed() { return speed; }
    const std::type_info& get_type() { return typeid(OrbitalProj); }
    bool destroy_self() { return destruct; }
    int get_damage() { return damage; }

    void update(double dt, Engine::Systems& sys);
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

    Position anchor;
    double radius = 12.0;

};

}
