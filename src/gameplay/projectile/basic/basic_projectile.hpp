#pragma once

#include "component.hpp"
#include "deps.hpp"

#include "gameplay/projectile/i_projectile.hpp"
#include "timer.hpp"

namespace Game {

class BasicProjectile : public IProjectile {

public:

    BasicProjectile() {};

    BasicProjectile(Vector2 position, Vector2 direction, double speed, bool foe) : 
        pos(position), direction(direction), speed(speed), foe(foe) {

        hitbox.y = position.y;
        hitbox.x = position.x;
    }

    bool is_foe() override { return foe; }
    Rectangle get_hitbox() override { return hitbox; }
    Vector2 get_position() override { return pos; }
    double get_speed() override { return speed; }

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0) override {

        this->pos = pos;
        this->speed = speed;
        this->direction = direction;
        this->foe = foe;
        this->self_destruct = false;
        this->damage = damage == 0? this->damage : damage;

    }

    void update(double dt, Engine::Systems& sys) override;
    void draw() override;
    const std::type_info& get_type() override { return typeid(BasicProjectile); };
    bool destroy_self() override { return self_destruct; };
    int get_damage() override { return damage; };

public:

    bool foe = false;
    Rectangle hitbox = Rectangle{0, 0, 5, 5};
    Vector2 pos;
    double speed = 0;
    Vector2 direction{0, 0};
    int damage = 1;

    bool self_destruct = false;
};

}
