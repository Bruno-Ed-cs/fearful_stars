#pragma once

#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/i_enemy.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "raylib.h"

namespace Game {

class BasicEnemy : public IEnemy {

public:

    Engine::ComponentContainer components;

    BasicEnemy(Vector2 position) :
        position(position) {

        make_components();

    };

    BasicEnemy() {

        make_components();

    };

    void draw() override;
    void update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man, PlayerMan& player_man) override;
    void reset(Vector2 position) override;
    void take_damage(EnemyMan& enemy_man) override;
    Vector2 get_position() override { return position; };
    Engine::ComponentContainer& get_components() override { return components; };


public:

    Vector2 position {200, 50};
    Vector2 direction {0,1};
    double speed {1};

private:

    void make_components() {

        Engine::IComponent* comps[] = {

            new Health(2),
            new Hitbox(10.0, 10.0)

        };

        components = Engine::ComponentContainer{ comps }; 
    }


    
};

}
