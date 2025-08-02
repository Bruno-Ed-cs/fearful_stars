#pragma once 

#include "deps.hpp"
#include "projectile.hpp"
#include <iostream>

namespace game {

enum struct ProjType {

    basic
};

struct CollisionRes {

    bool collided;
    Projectile& projectile;
};

template <typename T>
concept is_projectilile = std::is_base_of_v<Projectile, T>;

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
            s_projectiles.emplace_back(
                std::make_unique<Proj>(pos, direction, speed, foe));

        } else {

            std::cout << "found remaking\n";
        
            auto& proj = s_projectiles[response.projectile_index];
            proj->set_position(pos);
            proj->set_direction(direction);
            proj->set_speed(speed);
            proj->set_foe(foe);
            proj->set_active(true);

        }

    }

private: 

    static std::vector<std::unique_ptr<Projectile>> s_projectiles;

    struct QuerryRes {

        size_t projectile_index;
        bool not_found;
    };

    template<is_projectilile Proj>
    static QuerryRes find_inactive() {

        QuerryRes response{0, true};

        for (size_t i = 0; i < s_projectiles.size(); ++i) {

            if (!s_projectiles[i]->is_active() && typeid(*s_projectiles[i]) == typeid(Proj)) {

                response.projectile_index = i;
                response.not_found = false;
                break;
            }

        }

        return response;

    }

};


}
