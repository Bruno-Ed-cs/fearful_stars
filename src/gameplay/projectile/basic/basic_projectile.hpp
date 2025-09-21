#pragma once

#include "deps.hpp"

#include "../i_projectile.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "timer.hpp"

namespace Game {

class BasicProjectile : public IProjectile {

public:

    BasicProjectile() = default;

    BasicProjectile(Vector2 position, Vector2 direction, double speed, bool foe) : 
        pos(position), direction(direction), speed(speed), foe(foe) {

        hitbox.y = position.y;
        hitbox.x = position.x;
    }

    bool is_foe() override { return foe; }
    Rectangle get_hitbox() override { return hitbox; }
    Vector2 get_position() override { return pos; }
    double get_speed() override { return speed; }

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe) override {

        this->pos = pos;
        this->speed = speed;
        this->direction = direction;
        this->foe = foe;

    }

    void update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) override;
    void draw() override;
    const std::type_info& get_type() override { return typeid(BasicProjectile); };
    Engine::ComponentContainer& get_components() override { return components; };

public:

    bool foe = false;
    Rectangle hitbox = Rectangle{0, 0, 5, 5};
    Vector2 pos;
    double speed = 0;
    Vector2 direction{0, 0};
    Engine::ComponentContainer components;
};

}
