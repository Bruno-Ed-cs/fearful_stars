#pragma once

#include "deps.hpp"
#include "i_enemy.hpp"
#include "systems.hpp"
#include <type_traits>

namespace Game {

template<typename Enemy>
concept is_enemy = std::is_base_of_v<IEnemy, Enemy> && std::is_default_constructible_v<Enemy>;

class EnemyMan {


public:

    struct Collision {

        bool has_collided;
        std::list<uint32_t> enemy_ids;

    };

    EnemyMan() {

        m_enemies_dock = std::vector<EnemyContainer>();

    }

    void update(double dt, Engine::Systems& sys);
    uint32_t get_enemy(IEnemy* enemy_ptr);
    IEnemy& get_enemy(uint32_t enemy_id);
    uint32_t insert_enemy(std::unique_ptr<IEnemy> enemy);
    uint32_t emplace_enemy(std::string_view enemy_type, Vector2 position);
    bool enemy_exists(uint32_t enemy_id);
    void append_delete_queue(uint32_t target_id);
    void draw();
    EnemyMan::Collision check_collisions(Rectangle collider);
    bool no_enemy_left();

    void debug_world();
    void debug_ui();

    template<is_enemy Enemy>
    static std::unique_ptr<Enemy> make_enemy() {

        auto enemy_ptr = std::make_unique<Enemy>();
        
        return std::move(enemy_ptr);

    }

    Rectangle despawn_rect = Rectangle{-50, -50, 420, 280};

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
