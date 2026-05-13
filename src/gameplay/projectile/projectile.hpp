#pragma once 

#include "deps.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/player/player.hpp"
#include "entity.hpp"
#include "id_generator.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include <memory>

namespace Game {

class Projectile : public Engine::Entity{
//    please have a default constructor
//    for the projectile manager

public:

    virtual bool is_foe() = 0;
    virtual Rectangle get_hitbox() = 0;
    virtual Vector2 get_position() = 0;
    virtual double get_speed() = 0;
    virtual int get_damage() = 0;
    virtual const std::type_info& get_type() = 0;

    virtual void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0) = 0;

    virtual ~Projectile() = default;
};

template <typename T>
concept is_projectile = std::is_base_of_v<Projectile, T> && std::is_default_constructible_v<T>;

class ProjectileMan {

public:

    struct Collision {

        bool collided;
        std::list<int32_t> targets;
    };

    ProjectileMan() :
        m_projectiles(), m_delete_queue() {}

    void update(double dt, Engine::Systems& sys);
    void draw();
    void debug_ui();
    void debug_world();
    void append_delete_queue(uint32_t id);
    uint32_t get_id(Projectile* target);
    Collision check_collisions(Rectangle collider, bool colide_foe);
    Projectile& get_projectile(uint32_t id);
    bool exists(uint32_t id);

    template<is_projectile Proj>
    void insert_projectile(std::unique_ptr<Proj> projectile) {

        //   std::cout << "not found making new\n";

        auto id_exists = [this](uint32_t id) {

            for (auto& projectile : m_projectiles) {
                if (projectile.id == id)
                    return true;
            }
            return false;
        };

        uint32_t id = Engine::generate_id<ProjectileMan>(id_exists);

        //std::print("{} \n", id);
        //  std::cout << "New projectile position: (" << pos.get_real().x << ", " << pos.get_real().y << ")\n";

        m_projectiles.emplace_back(
            std::move(projectile), 
            true,
            Engine::Timer(s_inactive_deadtime),
            id);

    }

    template<is_projectile Proj>
        uint32_t emplace(Vector2 pos,
                Vector2 direction,
                double speed,
                bool foe) {

            //std::cout << "bullet requested\n";
            QuerryRes response = find_inactive<Proj>();

            if (response.not_found) {

                //   std::cout << "not found making new\n";

                auto proj = make_projectile<Proj>(pos, direction, speed, foe);

                auto id_exists = [this](uint32_t id) {

                    for (auto& projectile : m_projectiles) {
                        if (projectile.id == id)
                            return true;
                    }
                    return false;
                };

                uint32_t id = Engine::generate_id<ProjectileMan>(id_exists);

                //std::print("{} \n", id);
                //  std::cout << "New projectile position: (" << pos.get_real().x << ", " << pos.get_real().y << ")\n";

                m_projectiles.emplace_back(
                        std::move(proj), 
                        true,
                        Engine::Timer(s_inactive_deadtime),
                        id);

                return id;
            } else {

                //std::cout << "found remaking\n";

                auto& proj = m_projectiles[response.projectile_index];
                proj.projectile_ptr->reset(pos, speed, direction, foe);
                proj.active = true;

                return proj.id;
            }

        }

    template<is_projectile Projectile>
        static std::unique_ptr<Projectile> make_projectile(Vector2 pos,
                Vector2 direction,
                double speed,
                bool foe) {

            auto proj = std::make_unique<Projectile>();
            proj->reset(pos, speed, direction, foe);
            return std::move(proj);
        };


    template<is_projectile Projectile>
        static std::unique_ptr<Projectile> make_projectile() {

            auto proj = std::make_unique<Projectile>();
            return std::move(proj);
        };

private:

    struct QuerryRes {

        size_t projectile_index;
        bool not_found;
    };

    struct ProjContainer {

        std::unique_ptr<Projectile> projectile_ptr;
        bool active;
        Engine::Timer deadtime;
        uint32_t id;
    };

    std::vector<ProjContainer> m_projectiles;
    std::queue<uint32_t> m_delete_queue;

    constexpr static double s_inactive_deadtime = 2.0f;

    void delete_projectile(uint32_t id);
    void deactivate_projectile(uint32_t id);

    template<is_projectile Proj>
        QuerryRes find_inactive() {

            QuerryRes response{0, true};

            for (size_t i = 0; i < m_projectiles.size(); ++i) {

                if (!m_projectiles[i].active && 
                        m_projectiles[i].projectile_ptr != nullptr &&
                        m_projectiles[i].projectile_ptr->get_type() == typeid(Proj)) {

                    response.projectile_index = i;
                    response.not_found = false;
                    break;
                }

            }

            return response;

        }


};


}
