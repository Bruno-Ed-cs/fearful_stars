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

    void init () {

        direction  = Direction{0,0};
        speed = 40;
        hp = Health(10);
        hitbox = Hitbox(16, 22);

        self_destruct = false;

        sprite = Engine::AssetMan::get_texture("eye");
    }

    Engine::Timer shot_cooldown{2.0f};
    Engine::Timer chain_cooldown{0.1};
    int shot_count = 0;

    bool in_position = false;
    Vector2 target_pos{0,0};

    
};

}

