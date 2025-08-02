#include "deps.hpp"

#include "gameplay/projectile/projectile.hpp"
#include "projectile_manager.hpp"
#include "basic_projectile.hpp"
#include "globals.hpp"

using namespace game;

std::vector<std::unique_ptr<Projectile>> ProjectileMan::s_projectiles;

//CollisionRes ProjectileMan::check_collision(Rectangle target) {

//}

void ProjectileMan::update(double dt) {

    std::cout << "update\n" << s_projectiles.size() << '\n';

    for (size_t i = 0; i < s_projectiles.size(); ++i) {


        if (s_projectiles[i]->is_active()) {

            s_projectiles[i]->update(dt);

            std::cout << i << "  past update" << '\n';
            auto pos = s_projectiles[i]->get_position().get_round();

            if ((pos.x > engine::g_canva_size.x || pos.x < 0) ||
                (pos.y > engine::g_canva_size.y || pos.y < 0))
                s_projectiles[i]->set_active(false);

        }

    }

}

void ProjectileMan::draw() {

    for (size_t i = 0; i < s_projectiles.size(); ++i) {

        if (s_projectiles[i]->is_active()) {

            s_projectiles[i]->draw();

        }

    }

}

