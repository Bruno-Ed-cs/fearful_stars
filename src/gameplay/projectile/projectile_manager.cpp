#include "deps.hpp"

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "projectile_manager.hpp"
#include "basic/basic_projectile.hpp"
#include "globals.hpp"
#include "imgui.h"
#include <stdexcept>

using namespace Game;

//CollisionRes ProjectileMan::check_collision(Rectangle target) {

//}

void ProjectileMan::update(double dt, EnemyMan& enemy_man) {

//    std::cout << "update\n" << m_projectiles.size() << '\n';

    while (!m_delete_queue.empty()) {

        uint32_t id = m_delete_queue.front();

        m_delete_queue.pop();

        delete_projectile(id);

    }

    for (size_t i = 0; i < m_projectiles.size(); ++i) {

        auto& cur_proj = m_projectiles[i];

        if (cur_proj.active) {

            cur_proj.projectile_ptr->update(dt, enemy_man, *this);

 //           std::cout << i << "  past update" << '\n';
            auto pos = cur_proj.projectile_ptr->get_position();

            if ((pos.x > Engine::g_canva_size.x || pos.x < 0) ||
                (pos.y > Engine::g_canva_size.y || pos.y < 0)) {

                cur_proj.active = false;
                cur_proj.deadtime.reset();
            }

        } else {

            cur_proj.deadtime.update(dt);

            if (cur_proj.deadtime.past_limit()) {

                m_projectiles.erase(m_projectiles.begin() + i);
            }
        }

    }
}

void ProjectileMan::draw() {

    for (size_t i = 0; i < m_projectiles.size(); ++i) {

        auto& cur_proj = m_projectiles[i];

        if (cur_proj.active) {

            cur_proj.projectile_ptr->draw();

        }

    }

}

void ProjectileMan::debug() {


    static bool window_open = false;

    ImGui::Begin("Projectile Manager Debug", &window_open);
    {

        ImGui::Text("Projectiles in buffer: %d", (int)m_projectiles.size());

        int active_proj = 0;
        for (auto& proj : m_projectiles) {

            if (proj.active) ++active_proj;
        }

        ImGui::Text("Active Projectiles: %d", active_proj);
        ImGui::Text("Inactive Projectiles: %d", (int)m_projectiles.size() - active_proj);


    }
    ImGui::End();

}

void ProjectileMan::delete_projectile(uint32_t id) {

    for (size_t i = 0; i < m_projectiles.size(); ++i) {

        if (m_projectiles[i].id == id) {

            m_projectiles.erase(m_projectiles.begin() + i);

            break;

        }

    }

}

void ProjectileMan::deactivate_projectile(uint32_t id) {

    for (size_t i = 0; i < m_projectiles.size(); ++i) {

        if (m_projectiles[i].id == id) {

            m_projectiles[i].active = false;

            break;

        }

    }

}

uint32_t ProjectileMan::get_id(IProjectile* target) {

    for (size_t i = 0; i < m_projectiles.size(); ++i) {

        if (m_projectiles[i].projectile_ptr.get() == target) {

            return m_projectiles[i].id;
        }

    }

    throw std::logic_error("id not found");
}

void ProjectileMan::append_delete_queue(uint32_t id) {

    m_delete_queue.push(id);

}

