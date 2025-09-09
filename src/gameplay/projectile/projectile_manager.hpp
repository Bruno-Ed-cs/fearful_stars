#pragma once 

#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "i_projectile.hpp"
#include "id_generator.hpp"
#include "timer.hpp"

namespace Game {

struct CollisionRes {

    bool collided;
    IProjectile& projectile;
};

template <typename T>
concept is_projectile = std::is_base_of_v<IProjectile, T> && std::is_default_constructible_v<T>;

class ProjectileMan {

public:

    ProjectileMan() :
        m_projectiles(), m_delete_queue() {}

    void update(double dt, EnemyMan& enemy_man);
    void draw();
    void debug();
    void append_delete_queue(uint32_t id);
    uint32_t get_id(IProjectile* target);

    template<is_projectile Proj>
    void create_projectile(Vector2 pos,
                           Vector2 direction,
                           double speed,
                           bool foe) {

        //std::cout << "bullet requested\n";
        QuerryRes response = find_inactive<Proj>();

        if (response.not_found) {

            //   std::cout << "not found making new\n";

            auto proj = std::make_unique<Proj>();
            proj->reset(pos, speed, direction, foe);

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

        } else {

            //std::cout << "found remaking\n";

            auto& proj = m_projectiles[response.projectile_index];
            proj.projectile_ptr->reset(pos, speed, direction, foe);
            proj.active = true;

        }

    }



private: 


    struct QuerryRes {

        size_t projectile_index;
        bool not_found;
    };

    struct ProjContainer {

        std::unique_ptr<IProjectile> projectile_ptr;
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
