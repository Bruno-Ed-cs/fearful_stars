#include "enemy_man.hpp"
#include "libs/id_generator.hpp"
#include <stdexcept>

using namespace Game;


void EnemyMan::update(double dt) {

    while (!m_delete_queue.empty()) {

        destroy_enemy(m_delete_queue.front());
        m_delete_queue.pop();

    }

    for(size_t i = 0; i < m_enemies_dock.size(); ++i) {

        m_enemies_dock[i].enemy->update(dt, *this);

    }

}

uint32_t EnemyMan::insert_enemy(std::unique_ptr<IEnemy> enemy) {

    auto ver_id = [this](uint32_t id) { return this->enemy_exists(id); };

    uint32_t id = Engine::generate_id<EnemyMan>(ver_id);

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

void EnemyMan::append_delete_queue(uint32_t target_id) {

    m_delete_queue.push(target_id);

}

uint32_t EnemyMan::get_enemy(IEnemy* enemy_ptr) {

    for (size_t i = 0; i < m_enemies_dock.size(); ++i) {

        if (m_enemies_dock[i].enemy.get() == enemy_ptr) {

            return m_enemies_dock[i].id;
        }

    }

    throw std::logic_error("id not found");

}

