#pragma once

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

    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;

    void init () {

        direction  = Direction{-1,0};
        speed = 40;
        hp = Health(5);
        hitbox = Hitbox(24, 16);

        self_destruct = false;

        //sprite;
    }

    Engine::Timer pick_direction {2.0f};
    Engine::Timer decision_making {1.0f};
    Engine::Timer shot_cooldown {3.0f};

};

}

