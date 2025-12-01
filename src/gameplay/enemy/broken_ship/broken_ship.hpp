#pragma once

#include "deps.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"

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

    void draw() override;
    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;

    void init () {

        direction  = Direction{-1,0};
        speed = 80;
        hp = Health(5);
        hitbox = Hitbox(24, 16);

        self_destruct = false;

        //sprite;
    }

};

}

