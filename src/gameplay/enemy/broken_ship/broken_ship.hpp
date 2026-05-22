#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "timer.hpp"

namespace Game {

class BrokenShip : public BasicEnemy {

public:

    BrokenShip() {
        pos = Position();
        init();

    }

    BrokenShip(Vector2 position) {
        init();
        pos = position;

    }

    void update(double dt, Engine::GameState& sys) override;
    void reset(Vector2 position) override;
    EnemyType get_type() override { return EnemyType::BrokenShip; };
    void init () {

        direction  = Direction{-1,0};
        speed = 40;
        hp = Health(5);
        hitbox = Hitbox(24, 16);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("broken_ship");
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

    Engine::Timer pick_direction {2.0f};
    Engine::Timer decision_making {1.0f};
    Engine::Timer shot_cooldown {3.0f};

};

}

