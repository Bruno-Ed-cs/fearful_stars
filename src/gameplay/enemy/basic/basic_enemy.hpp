#pragma once

#include "deps.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/i_enemy.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "raylib.h"
#include "systems.hpp"

namespace Game {

class BasicEnemy : public IEnemy {

public:

    Engine::ComponentContainer components;

    BasicEnemy(Vector2 position) {

        make_components();

        components.get<Position>() = position;

    };

    BasicEnemy() {

        make_components();

    };

    void draw() override;
    void update(double dt, Engine::Systems& sys) override;
    void reset(Vector2 position) override;
    void take_damage(EnemyMan& enemy_man, int damage) override;
    Engine::ComponentContainer& get_components() override { return components; };


public:

    Vector2 direction {0,1};
    double speed {1};

private:

    void make_components() {

        components = Engine::ComponentContainer{ 

            new Health(2),
            new Hitbox(10.0, 10.0),
            new Position(200, 50)
        }; 
    }



};

}
