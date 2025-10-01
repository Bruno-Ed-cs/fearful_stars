#pragma once

#include "deps.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "i_enemy.hpp"
#include <memory>

namespace Game {

class EnemyMan {

public:

    struct Collision {

        bool has_collided;
        uint32_t enemy_id;

    };

    EnemyMan() {

        m_enemies_dock = std::vector<EnemyContainer>();

    }

    void update(double dt, ProjectileMan& projectile_man, PlayerMan& player_man);
    uint32_t get_enemy(IEnemy* enemy_ptr);
    IEnemy& get_enemy(uint32_t enemy_id);
    uint32_t insert_enemy(std::unique_ptr<IEnemy> enemy);
    uint32_t emplace_enemy(std::string_view enemy_type, Vector2 position);
    bool enemy_exists(uint32_t enemy_id);
    void append_delete_queue(uint32_t target_id);
    void draw();
    EnemyMan::Collision check_collisions(Rectangle collider);

    template<typename Enemy>
    static std::unique_ptr<Enemy> make_enemy(Vector2 pos) {

        auto enemy_ptr = std::make_unique<Enemy>(pos);
        
        return std::move(enemy_ptr);

    }

private:

    struct EnemyContainer {
        std::unique_ptr<IEnemy> enemy;
        uint32_t id;
    };

    std::vector<EnemyContainer> m_enemies_dock;
    std::queue<uint32_t> m_delete_queue;

    size_t get_index(uint32_t enemy_id);
    void destroy_enemy(uint32_t enemy_id);

};

}
