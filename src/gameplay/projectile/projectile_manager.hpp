#pragma once 

#include "deps.hpp"
#include "projectile.hpp"
#include "timer.hpp"

namespace game {

struct CollisionRes {

    bool collided;
    Projectile& projectile;
};

template <typename T>
concept is_projectilile = std::is_base_of_v<Projectile, T> && std::is_default_constructible_v<T>;

class ProjectileMan {

public:

//    static CollisionRes check_collision(Rectangle target);
    static void update(double dt);
    static void draw();

    template<is_projectilile Proj>
    static void request_projectile(engine::Position pos,
                                   Vector2 direction,
                                   double speed,
                                   bool foe) {
        
        std::cout << "bullet requested\n";
        QuerryRes response = find_inactive<Proj>();

        if (response.not_found) {

            std::cout << "not found making new\n";

            auto proj = std::make_unique<Proj>();
            proj->reset(pos, speed, direction, foe);
            std::cout << "New projectile position: (" << pos.get_real().x << ", " << pos.get_real().y << ")\n";
            
            s_projectiles.emplace_back(
                std::move(proj), 
                true,
                engine::Timer(s_inactive_deadtime));

        } else {

            std::cout << "found remaking\n";
        
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

        std::unique_ptr<Projectile> proj_uptr;
        bool active;
        engine::Timer deadtime;
    };

    static std::vector<ProjContainer> s_projectiles;

    constexpr static double s_inactive_deadtime = 2.0f;

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
