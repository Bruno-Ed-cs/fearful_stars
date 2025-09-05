#pragma once

#include "deps.hpp"
#include "i_enemy.hpp"
#include <cstdint>
#include <utility>

namespace Game {


struct EnemyCollision {

    bool has_collided;
    uint32_t enemy_id;

};

enum struct EnemyEvent {
    take_damage

};


class EnemyMan {

public:

    EnemyMan() {

        m_enemies_dock = std::vector<EnemyContainer>();

    }

    void update(double dt);
    uint32_t get_enemy(IEnemy* enemy_ptr);
    uint32_t insert_enemy(std::unique_ptr<IEnemy> enemy);
    bool enemy_exists(uint32_t enemy_id);
    void append_delete_queue(uint32_t target_id);
    void draw();
    EnemyCollision check_collisions(Rectangle collider);

    template<typename... Args>
    void trigger_event(uint32_t target_id, EnemyEvent event, Args&&... args) {

        IEnemy& target = *m_enemies_dock[get_index(target_id)].enemy.get();

        switch (event) {

            case EnemyEvent::take_damage:
                target.take_damage(std::forward<Args>(args)...);
                break;

            default:
                throw std::logic_error("Event not found");


        }
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
