#pragma once

#include "deps.hpp"
#include "i_enemy.hpp"

namespace Game {


struct EnemyCollision {

    bool has_collided;
    uint32_t enemy_id;

};


class EnemyMan {

public:

    EnemyMan() {

        m_enemies_dock = std::vector<EnemyContainer>();

    }

    void update(double dt);
    uint32_t insert_enemy(std::unique_ptr<IEnemy> enemy);
    void destroy_enemy(uint32_t enemy_id);
    bool enemy_exists(uint32_t enemy_id);
    void draw();
    EnemyCollision check_collisions(Rectangle collider);

private:

    struct EnemyContainer {
        std::unique_ptr<IEnemy> enemy;
        uint32_t id;
    };

    std::vector<EnemyContainer> m_enemies_dock;

    uint32_t generate_id();
    size_t get_index(uint32_t enemy_id);

};

}
