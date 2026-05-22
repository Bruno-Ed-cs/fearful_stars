#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "timer.hpp"

namespace Game {

class Vagant : public BasicEnemy {

public:

    Vagant() {
        pos = Position();
        init();

    }

    Vagant(Vector2 position) {
        init();
        pos = position;

    }

    void update(double dt, Engine::GameState& sys) override;
    void reset(Vector2 position) override;
    EnemyType get_type() override { return EnemyType::Vagant; };
    void init () {

        direction  = Direction{-1,0};
        speed = 30;
        hp = Health(50);
        hitbox = Hitbox(70, 30);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("vagant");
    }

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

    Engine::Timer shot_cooldown{0.5f};

};

}

