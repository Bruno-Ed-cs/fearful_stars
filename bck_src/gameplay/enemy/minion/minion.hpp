#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "timer.hpp"

namespace Game {

class Minion : public BasicEnemy {

public:

    Minion() {
        pos = Position();
        init();

    }

    Minion(Vector2 position) {
        init();
        pos = position;

    }

    void update(double dt, Engine::GameState& sys) override;
    void reset(Vector2 position) override;
    EnemyType get_type() override { return EnemyType::Minion; };
    void init () {

        direction  = Direction{-1,0};
        speed = 80;
        hp = Health(40);
        hitbox = Hitbox(18, 28);

        self_destruct = false;

        targets = std::to_array({Vector2{300, 90},
                                Vector2{190, 90},
                                Vector2{288, 10},
                                Vector2{288, 170}}
                                );



        sprite = Engine::AssetMan::get_texture("minion");
    }

    Engine::Package package() override {
        Engine::Package pack;
        pack["direction_x"] = std::to_string(direction.x);
        pack["direction_y"] = std::to_string(direction.y);
        pack["speed"] = std::to_string(speed);
        pack["hp"] = std::to_string(hp.points);
        pack["pos_x"] = std::to_string(pos.x);
        pack["pos_y"] = std::to_string(pos.y);
        pack["cur_target"] = std::to_string(cur_target);

        return pack;
    };

    void unpack(Engine::Package pack) override {
        direction = Vector2{ std::stof(pack["direction_x"]), std::stof(pack["direction_y"]) };
        pos = Position(std::stod(pack["pos_x"]), std::stod(pack["pos_y"]));
        speed = std::stod(pack["speed"]);
        hp = Health(std::stoi(pack["hp"]));
        cur_target = std::stoi(pack["cur_target"]);
    }

    Engine::Timer shot_cooldown{1.5f};

    int cur_target = 0;

    std::array<Vector2, 4> targets;



};

}

