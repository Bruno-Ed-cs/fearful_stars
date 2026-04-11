#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/components.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "systems.hpp"

namespace Game {

class PlasmaProj : public IProjectile{

public:

    PlasmaProj() {

        sprite = Engine::AssetMan::get_texture("plasma_proj");

    }
    PlasmaProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {

        sprite = Engine::AssetMan::get_texture("plasma_proj");
    }

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
    std::shared_ptr<Texture> sprite;

};

}
