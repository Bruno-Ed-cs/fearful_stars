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

    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;

    void init () {

        direction  = Direction{-1,0};
        speed = 80;
        hp = Health(20);
        hitbox = Hitbox(18, 28);

        self_destruct = false;

        targets = std::to_array({Vector2{300, 90},
                                Vector2{190, 90},
                                Vector2{288, 10},
                                Vector2{288, 170}}
                                );



        sprite = Engine::AssetMan::get_texture("minion");
    }

    Engine::Timer shot_cooldown{1.5f};

    int cur_target = 0;

    std::array<Vector2, 4> targets;



};

}

