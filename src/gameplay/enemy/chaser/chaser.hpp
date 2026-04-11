#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/components.hpp"
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

    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;

    void init () {

        direction  = Direction{-1,0};
        speed = 70;
        hp = Health(15);
        hitbox = Hitbox(28, 20);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("chaser");
    }

    Engine::Timer player_pos_update{3.0f};
    Vector2 player_pos;
};

}

