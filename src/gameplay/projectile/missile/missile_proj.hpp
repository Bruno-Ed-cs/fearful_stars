#pragma once

#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "systems.hpp"

namespace Game {

class MissileProj : public IProjectile{

public:

    MissileProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {}

    bool is_foe() { return foe; }
    Rectangle get_hitbox() { return hitbox.get(pos); }
    Vector2 get_position() { return pos.vec(); }
    double get_speed() { return speed; }
    const std::type_info& get_type() { return typeid(MissileProj); }
    bool destroy_self() { return destruct; }

    void update(double dt, Engine::Systems& sys);
    void draw();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0);

public:

    Position pos;
    Direction orientation;
    Hitbox hitbox = Hitbox(10, 6);
    int damage;
    double speed;
    bool foe;
    bool destruct = false;

};

}
