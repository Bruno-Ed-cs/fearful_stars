#pragma once

#include "asset_man.hpp"
#include "component.hpp"
#include "deps.hpp"

#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "timer.hpp"

namespace Game {

class BasicProjectile : public IProjectile {

public:

    BasicProjectile() {

        sprite = Engine::AssetMan::get_texture("basic_proj");

    };

    BasicProjectile(Vector2 position, Vector2 direction, double speed, bool foe) : 
        pos(position), direction(direction), speed(speed), foe(foe) {

        sprite = Engine::AssetMan::get_texture("basic_proj");
    }

    bool is_foe() override { return foe; }
    Rectangle get_hitbox() override { return hitbox.get(pos); }
    Vector2 get_position() override { return pos.vec(); }
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
    Hitbox hitbox = Hitbox{5, 5};
    Position pos;
    double speed = 0;
    Vector2 direction{0, 0};
    int damage = 1;

    bool self_destruct = false;

    std::shared_ptr<Texture> sprite;
};

}
