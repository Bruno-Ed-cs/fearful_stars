#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "systems.hpp"

namespace Game {

class BigShotProj : public Projectile{

public:

    BigShotProj() {

        sprite = Engine::AssetMan::get_texture("super_proj");

    }
    BigShotProj(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {

        sprite = Engine::AssetMan::get_texture("super_proj");
    }

    bool is_foe() { return foe; }
    Rectangle get_hitbox() { return hitbox.get(pos); }
    Vector2 get_position() { return pos.vec(); }
    double get_speed() { return speed; }
    const std::type_info& get_type() { return typeid(BigShotProj); }
    bool destroy_self() { return destruct; }
    int get_damage() { return damage; }

    void update(double dt, Engine::Systems& sys);
    void draw();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0);

public:

//Inicialize as variaveis 

    Position pos;
    Direction orientation;
    Hitbox hitbox = Hitbox(92, 64);
    int damage = 5;
    double speed = 100;
    bool foe = false;
    bool destruct = false;

    std::shared_ptr<Texture> sprite;

};

}
