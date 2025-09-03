#include "enemy_man.hpp"
#include "raylib.h"

using namespace Game;


void EnemyMan::update(double dt) {

    for(size_t i = 0; i < m_enemies_dock.size(); ++i) {

        m_enemies_dock[i].enemy->update(dt, *this);

    }

}

uint32_t EnemyMan::insert_enemy(std::unique_ptr<IEnemy> enemy) {

    uint32_t id = generate_id();

    m_enemies_dock.emplace_back(
        std::move(enemy),
        id
    );

    return id;
}

void EnemyMan::destroy_enemy(uint32_t enemy_id) {

    if (!enemy_exists(enemy_id)) {
        throw std::runtime_error("Tried to destroy a enemy that does not exists");
    }

    uint32_t index = get_index(enemy_id);

    m_enemies_dock.erase(m_enemies_dock.begin() + index);

}

uint32_t EnemyMan::generate_id() {

    constexpr const uint32_t int_lim_32 = 4294967295;

    static uint32_t biggest_id = 0;

    if (biggest_id == int_lim_32) {

        uint32_t ran_id = rand() % int_lim_32;
        while (enemy_exists(ran_id)) {

            ran_id = rand() % int_lim_32;
        }

        return ran_id;

    } else {

        biggest_id++;
        return biggest_id;

    }
}

bool EnemyMan::enemy_exists(uint32_t enemy_id) {

    bool exists = false;

    for (size_t i = 0; i < m_enemies_dock.size(); ++i) {

        if (m_enemies_dock[i].id == enemy_id) {
            exists = true;
            break;
        }

    }

    return exists;

}

size_t EnemyMan::get_index(uint32_t enemy_id) {

    size_t index = 0;
    for (; m_enemies_dock[index].id != enemy_id; ++index);

    return index;

}

void EnemyMan::draw() {

    for(size_t i = 0; i < m_enemies_dock.size(); ++i) {

        m_enemies_dock[i].enemy->draw();

    }
}

EnemyCollision EnemyMan::check_collisions(Rectangle collider) {

    uint32_t enemy_id = 0;
    bool collided = false;

    for (auto& enemy_container : m_enemies_dock) {

        if (CheckCollisionRecs(collider, enemy_container.enemy->get_hitbox())) {

            collided = true;
            enemy_id = enemy_container.id;
            break;
        }

    }

    return EnemyCollision{collided, enemy_id};

}

