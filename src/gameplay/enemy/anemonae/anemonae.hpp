#pragma once

#include "deps.hpp"
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

    void draw() override;
    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;

    void init () {

        direction  = Direction{-1,0};
        speed = 50;
        hp = Health(10);
        hitbox = Hitbox(32, 32);

        self_destruct = false;

        //sprite;
    }

    Engine::Timer shot_cooldown{1.5f};
    float final_x = 0;

};

}

