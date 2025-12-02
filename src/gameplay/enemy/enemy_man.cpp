#include "enemy_man.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/enemy/anemonae/anemonae.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "gameplay/enemy/broken_ship/broken_ship.hpp"
#include "gameplay/enemy/chaser/chaser.hpp"
#include "gameplay/enemy/eye/crystal_eye.hpp"
#include "gameplay/enemy/minion/minion.hpp"
#include "gameplay/enemy/vagant/vagant.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "id_generator.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"

using namespace Game;

uint32_t EnemyMan::emplace_enemy(std::string_view enemy_type, Vector2 position) {

    if (enemy_type == "Basic") {

        auto enemy = EnemyMan::make_enemy<BasicEnemy>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));


    } else if (enemy_type == "BrokenShip") {

        auto enemy = EnemyMan::make_enemy<BrokenShip>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));

    } else if (enemy_type == "Anemonae") {

        auto enemy = EnemyMan::make_enemy<Anemonae>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));

    } else if (enemy_type == "Chaser") {

        auto enemy = EnemyMan::make_enemy<Chaser>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));

    } else if (enemy_type == "CrystalEye") {

        auto enemy = EnemyMan::make_enemy<CrystalEye>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));


    } else if (enemy_type == "Vagant") {

        auto enemy = EnemyMan::make_enemy<Vagant>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));


    } else if (enemy_type == "Minion") {

        auto enemy = EnemyMan::make_enemy<Minion>();
        enemy->reset(position);

        return insert_enemy(std::move(enemy));

    } else {

        throw std::invalid_argument(std::format("The enemy type {} does not exists", enemy_type));
    }

}

void EnemyMan::update(double dt, Engine::Systems& sys) {

    for (auto& container: m_enemies_dock) {

        if (container.enemy->destroy_self() ||
            !CheckCollisionRecs(despawn_rect, container.enemy->get_hitbox())) {

            append_delete_queue(container.id);
        } 

    }

    while (!m_delete_queue.empty()) {

        destroy_enemy(m_delete_queue.front());
        m_delete_queue.pop();

    }

    for(size_t i = 0; i < m_enemies_dock.size(); ++i) {

        m_enemies_dock[i].enemy->update(dt, sys);

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

void EnemyMan::debug_ui() {

};

void EnemyMan::debug_world() {

    Engine::RenderMan::begin_draw_debug();
    for (auto& container: m_enemies_dock) {

        DrawRectangleRec(container.enemy->get_hitbox(), RED);

    }
    Engine::RenderMan::end_draw_debug();

};

void EnemyMan::draw() {

    for(size_t i = 0; i < m_enemies_dock.size(); ++i) {

        m_enemies_dock[i].enemy->draw();

    }
}

EnemyMan::Collision EnemyMan::check_collisions(Rectangle collider) {

    std::list<uint32_t> enemy_ids;
    bool collided = false;

    for (auto& enemy_container : m_enemies_dock) {

        auto hitbox = enemy_container.enemy->get_hitbox();

        if (CheckCollisionRecs(collider, hitbox)) {

            collided = true;
            enemy_ids.push_back(enemy_container.id);
        }

    }

    return EnemyMan::Collision{collided, enemy_ids};

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

    throw std::logic_error("enemy not found");

}

IEnemy& EnemyMan::get_enemy(uint32_t enemy_id) {


    for (size_t i = 0; i < m_enemies_dock.size(); ++i) {

        if (m_enemies_dock[i].id == enemy_id) {

            return *m_enemies_dock[i].enemy;
        }

    }

    throw std::logic_error("id not found");

}

bool EnemyMan::no_enemy_left() {

    if (m_enemies_dock.empty())
        return true;

    return false;

}
