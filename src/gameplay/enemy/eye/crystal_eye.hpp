#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "timer.hpp"

namespace Game {

class CrystalEye : public BasicEnemy {

public:

    CrystalEye() {
        pos = Position();
        init();

    }

    CrystalEye(Vector2 position) {
        init();
        pos = position;

    }

    void update(double dt, Engine::GameState& sys) override;
    void reset(Vector2 position) override;
    EnemyType get_type() override { return EnemyType::CrystalEye; };
    void init () {

        direction  = Direction{0,0};
        speed = 40;
        hp = Health(10);
        hitbox = Hitbox(16, 22);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("eye");
    }

    Engine::Package package() override {
        Engine::Package pack;
        pack["direction_x"] = std::to_string(direction.x);
        pack["direction_y"] = std::to_string(direction.y);
        pack["speed"] = std::to_string(speed);
        pack["hp"] = std::to_string(hp.points);
        pack["pos_x"] = std::to_string(pos.x);
        pack["pos_y"] = std::to_string(pos.y);
        pack["shot_count"] = std::to_string(shot_count);
        pack["in_position"] = std::to_string(in_position);

        return pack;
    };

    void unpack(Engine::Package pack) override {
        direction = Vector2{ std::stof(pack["direction_x"]), std::stof(pack["direction_y"]) };
        pos = Position(std::stod(pack["pos_x"]), std::stod(pack["pos_y"]));
        speed = std::stod(pack["speed"]);
        hp = Health(std::stoi(pack["hp"]));

        shot_count = std::stoi(pack["shot_count"]);
        in_position = std::stoi(pack["in_position"]);
    }

    Engine::Timer shot_cooldown{2.0f};
    Engine::Timer chain_cooldown{0.1};
    int shot_count = 0;

    bool in_position = false;
    Vector2 target_pos{0,0};

    
};

}

