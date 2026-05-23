#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "entity.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "timer.hpp"

namespace Game {

class Anemonae : public BasicEnemy {

public:

    Anemonae() {
        pos = Position();
        init();

    }

    Anemonae(Vector2 position) {
        init();
        pos = position;

    }

    void update(double dt, Engine::GameState& sys) override;
    void reset(Vector2 position) override;
    EnemyType get_type() override { return EnemyType::Anemonae; };

    void init () {

        direction  = Direction{-1,0};
        speed = 50;
        hp = Health(30);
        hitbox = Hitbox(32, 32);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("anemonae");
    }

    Engine::Package package() override {
        Engine::Package pack;
        pack["direction_x"] = std::to_string(direction.x);
        pack["direction_y"] = std::to_string(direction.y);
        pack["speed"] = std::to_string(speed);
        pack["hp"] = std::to_string(hp.points);
        pack["pos_x"] = std::to_string(pos.x);
        pack["pos_y"] = std::to_string(pos.y);
        pack["final_x"] = std::to_string(final_x);

        return pack;
    };

    void unpack(Engine::Package pack) override {
        direction = Vector2{ std::stof(pack["direction_x"]), std::stof(pack["direction_y"]) };
        pos = Position(std::stod(pack["pos_x"]), std::stod(pack["pos_y"]));
        speed = std::stod(pack["speed"]);
        hp = Health(std::stoi(pack["hp"]));
        final_x = std::stof(pack["final_x"]);
    }

    Engine::Timer shot_cooldown{1.5f};
    float final_x = 0;

};

}

