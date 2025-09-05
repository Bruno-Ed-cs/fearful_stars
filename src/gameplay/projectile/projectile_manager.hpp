#pragma once 

#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "i_projectile.hpp"
#include "id_generator.hpp"
#include "timer.hpp"
#include <print>

namespace Game {

struct CollisionRes {

    bool collided;
    IProjectile& projectile;
};

template <typename T>
concept is_projectilile = std::is_base_of_v<IProjectile, T> && std::is_default_constructible_v<T>;

class ProjectileMan {

public:

    //    static CollisionRes check_collision(Rectangle target);
    static void update(double dt, EnemyMan& enemy_man);
    static void draw();
    static void debug();
    static void append_delete_queue(uint32_t id);
    static uint32_t get_id(IProjectile* target);


    template<is_projectilile Proj>
    static void request_projectile(Vector2 pos,
                                   Vector2 direction,
                                   double speed,
                                   bool foe) {

        //std::cout << "bullet requested\n";
        QuerryRes response = find_inactive<Proj>();

        if (response.not_found) {

            //   std::cout << "not found making new\n";

            auto proj = std::make_unique<Proj>();
            proj->reset(pos, speed, direction, foe);

            auto id_exists = [](uint32_t id) {

                for (auto& projectile : ProjectileMan::s_projectiles) {
                    if (projectile.id == id)
                        return true;
                }
                return false;
            };

            uint32_t id = Engine::generate_id<ProjectileMan>(id_exists);

            //std::print("{} \n", id);
            //  std::cout << "New projectile position: (" << pos.get_real().x << ", " << pos.get_real().y << ")\n";

            s_projectiles.emplace_back(
                std::move(proj), 
                true,
                Engine::Timer(s_inactive_deadtime),
                id);

        } else {

            //std::cout << "found remaking\n";

            auto& proj = s_projectiles[response.projectile_index];
            proj.proj_uptr->reset(pos, speed, direction, foe);
            proj.active = true;

        }

    }

private: 


    struct QuerryRes {

        size_t projectile_index;
        bool not_found;
    };

    struct ProjContainer {

        std::unique_ptr<IProjectile> proj_uptr;
        bool active;
        Engine::Timer deadtime;
        uint32_t id;
    };

    static std::vector<ProjContainer> s_projectiles;
    static std::queue<uint32_t> s_delete_queue;

    constexpr static double s_inactive_deadtime = 2.0f;

    static void delete_projectile(uint32_t id);
    template<is_projectilile Proj>
    static QuerryRes find_inactive() {

        QuerryRes response{0, true};

        for (size_t i = 0; i < s_projectiles.size(); ++i) {

            if (!s_projectiles[i].active && 
                s_projectiles[i].proj_uptr != nullptr &&
                typeid(*s_projectiles[i].proj_uptr) == typeid(Proj)) {

                response.projectile_index = i;
                response.not_found = false;
                break;
            }

        }

        return response;

    }


};


}
