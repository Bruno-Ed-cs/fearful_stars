#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "timer.hpp"

namespace Game {

class Chaser : public BasicEnemy {

public:

    Chaser() {
        pos = Position();
        init();

    }

    Chaser(Vector2 position) {
        init();
        pos = position;

    }

    void update(double dt, Engine::GameState& sys) override;
    void reset(Vector2 position) override;
    EnemyType get_type() override { return EnemyType::Chaser; };
    void init () {

        direction  = Direction{-1,0};
        speed = 70;
        hp = Health(15);
        hitbox = Hitbox(28, 20);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("chaser");
    }

    Engine::Package package() override {
        Engine::Package pack;
        pack["direction_x"] = std::to_string(direction.x);
        pack["direction_y"] = std::to_string(direction.y);
        pack["speed"] = std::to_string(speed);
        pack["hp"] = std::to_string(hp.points);
        pack["pos_x"] = std::to_string(pos.x);
        pack["pos_y"] = std::to_string(pos.y);
        pack["player_pos_x"] = std::to_string(player_pos.x);
        pack["player_pos_y"] = std::to_string(player_pos.y);

        return pack;
    };

    Engine::Timer player_pos_update{3.0f};
    Vector2 player_pos;
};

}

