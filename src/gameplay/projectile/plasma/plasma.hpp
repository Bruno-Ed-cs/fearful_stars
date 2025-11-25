#pragma once

#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "systems.hpp"

namespace Game {

class PlasmaProj : public IProjectile{

public:

    PlasmaProj() = default;
    PlasmaProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {}

    bool is_foe() override { return foe; }
    Rectangle get_hitbox() override { return hitbox.get(pos); }
    Vector2 get_position() override { return pos.vec(); }
    double get_speed() override { return speed; }
    int get_damage() override { return damage; }
    const std::type_info& get_type() override{ return typeid(PlasmaProj); }
    bool destroy_self() override { return destruct; }

    void update(double dt, Engine::Systems& sys) override;
    void draw() override;

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0) override;

public:

    Position pos = Position(0, 0);
    Direction orientation = Direction(0, 0);
    Hitbox hitbox = Hitbox(10, 6);
    int damage = 1;
    double speed = 50;
    bool foe = false;
    bool destruct = false;

};

}
