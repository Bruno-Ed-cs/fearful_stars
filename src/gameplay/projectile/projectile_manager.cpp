#include "deps.hpp"

#include "gameplay/projectile/projectile.hpp"
#include "projectile_manager.hpp"
#include "basic_projectile.hpp"
#include "globals.hpp"

using namespace game;

std::vector<ProjectileMan::ProjContainer> ProjectileMan::s_projectiles;


//CollisionRes ProjectileMan::check_collision(Rectangle target) {

//}

void ProjectileMan::update(double dt) {

    std::cout << "update\n" << s_projectiles.size() << '\n';

    for (size_t i = 0; i < s_projectiles.size(); ++i) {

        auto& cur_proj = s_projectiles[i];

        if (cur_proj.active) {

            cur_proj.proj_uptr->update(dt);

            std::cout << i << "  past update" << '\n';
            auto pos = cur_proj.proj_uptr->get_position().get_round();

            if ((pos.x > engine::g_canva_size.x || pos.x < 0) ||
                (pos.y > engine::g_canva_size.y || pos.y < 0)) {

                cur_proj.active = false;
                cur_proj.deadtime.reset();
            }

        } else {

            cur_proj.deadtime.update(dt);

            if (cur_proj.deadtime.past_limit()) {

                s_projectiles.erase(s_projectiles.begin() + i);
            }
        }

    }

}

void ProjectileMan::draw() {

    for (size_t i = 0; i < s_projectiles.size(); ++i) {

        auto& cur_proj = s_projectiles[i];

        if (cur_proj.active) {

            cur_proj.proj_uptr->draw();

        }

    }

}

