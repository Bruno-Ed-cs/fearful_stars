#pragma once

#include "asset_man.hpp"
#include "component.hpp"
#include "deps.hpp"
#include "entity.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "raylib.h"
#include "systems.hpp"

namespace Game {

class BasicEnemy : public Enemy {

public:


    BasicEnemy():
    pos(Vector2{100, 100}){

        sprite = Engine::AssetMan::get_texture("meteorite");

    };

    BasicEnemy(Vector2 position) :
        pos(position) {

        sprite = Engine::AssetMan::get_texture("meteorite");

    };


    void draw() override;
    virtual void update(double dt, Engine::GameState& sys) override;
    virtual void reset(Vector2 position) override;
    Rectangle get_hitbox() override { return hitbox.get(pos.vec()); };
    void take_damage(Engine::GameState& sys, int damage) override;
    EnemyType get_type() override { return EnemyType::Basic; };
    bool destroy_self() override { return self_destruct; };
    Vector2 get_position() override { return pos.vec(); };

    Engine::Package package() override {
        Engine::Package pack;
        pack["direction_x"] = std::to_string(direction.x);
        pack["direction_y"] = std::to_string(direction.y);
        pack["speed"] = std::to_string(speed);
        pack["hp"] = std::to_string(hp.points);
        pack["pos_x"] = std::to_string(pos.x);
        pack["pos_y"] = std::to_string(pos.y);

        return pack;
    };


public:

    Direction direction {-1,0};
    double speed {15};
    Health hp = Health(5);
    Hitbox hitbox = Hitbox(28, 22);
    Position pos;

    bool self_destruct = false;

    std::shared_ptr<Texture> sprite;

private:


};

}
