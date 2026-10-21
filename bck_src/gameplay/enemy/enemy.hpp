#pragma once

#include "deps.hpp"
#include "systems.hpp"
#include "entity.hpp"
#include <type_traits>

namespace Game {

template<typename Enemy>
concept is_enemy = std::is_base_of_v<Enemy, Enemy> && std::is_default_constructible_v<Enemy>;

enum class EnemyType {
    Anemonae = 1,
    Basic,
    BrokenShip,
    Chaser,
    CrystalEye,
    Minion,
    Vagant,

};

class Enemy : public Engine::Entity {

public:

    virtual void reset(Vector2 position) = 0;
    virtual void take_damage(Engine::GameState& sys, int damage) = 0;
    virtual EnemyType get_type() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual Vector2 get_position() = 0;
    

};

class EnemyMan {

public:

    struct Collision {

        bool has_collided;
        std::list<uint32_t> enemy_ids;

    };

    EnemyMan() {

        m_enemies_dock = std::vector<EnemyContainer>();

    }

    void update(double dt, Engine::GameState& sys);
    uint32_t get_enemy(Enemy* enemy_ptr);
    Enemy& get_enemy(uint32_t enemy_id);
    uint32_t insert_enemy(std::unique_ptr<Enemy> enemy);
    uint32_t emplace_enemy(std::string_view enemy_type, Vector2 position);
    bool enemy_exists(uint32_t enemy_id);
    void append_delete_queue(uint32_t target_id);
    void draw();
    EnemyMan::Collision check_collisions(Rectangle collider);
    bool no_enemy_left();
    void save_enemies(Engine::GameState& sys);
    void load_enemies(Engine::GameState& sys);

    void debug_world();
    void debug_ui();

    Enemy* make_enemy(EnemyType type);
    template<is_enemy Enemy>
    static std::unique_ptr<Enemy> make_enemy() {

        auto enemy_ptr = std::make_unique<Enemy>();
        
        return std::move(enemy_ptr);

    }

    Rectangle despawn_rect = Rectangle{-50, -50, 420, 280};

private:

    struct EnemyContainer {
        uint32_t id;
        std::unique_ptr<Enemy> enemy;
    };

    std::vector<EnemyContainer> m_enemies_dock;
    std::queue<uint32_t> m_delete_queue;


    size_t get_index(uint32_t enemy_id);
    void destroy_enemy(uint32_t enemy_id);

};

}
