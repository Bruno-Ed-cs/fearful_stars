#include "deps.hpp"

#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "projectile_manager.hpp"
#include "basic/basic_projectile.hpp"
#include "globals.hpp"
#include "imgui.h"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"

using namespace Game;

//CollisionRes ProjectileMan::check_collision(Rectangle target) {

//}

void ProjectileMan::update(double dt, Engine::Systems& sys) {

//    std::cout << "update\n" << m_projectiles.size() << '\n';

    for (auto& container: m_projectiles) {

        if (container.projectile_ptr->destroy_self() && container.active) {

            append_delete_queue(container.id);

        }

    }

    while (!m_delete_queue.empty()) {

        uint32_t id = m_delete_queue.front();

        m_delete_queue.pop();

        deactivate_projectile(id);

    }

    for (size_t i = 0; i < m_projectiles.size(); ++i) {

        auto& cur_proj = m_projectiles[i];

        if (cur_proj.active) {

            cur_proj.projectile_ptr->update(dt, sys);

 //           std::cout << i << "  past update" << '\n';
            auto pos = cur_proj.projectile_ptr->get_position();

            if ((pos.x > Engine::g_world_size.x || pos.x < 0) ||
                (pos.y > Engine::g_world_size.y || pos.y < 0)) {

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

void ProjectileMan::debug_world() {

    Engine::RenderMan::begin_draw_debug();


    for (auto& container : m_projectiles) {

        Color tint = BLUE;
        if (container.projectile_ptr->is_foe())
            tint = YELLOW;

        if (container.active)
            DrawRectangleRec(container.projectile_ptr->get_hitbox(), tint);

        else {

            tint.a = 100;

            DrawRectangleRec(container.projectile_ptr->get_hitbox(), tint);

        };
    };

    Engine::RenderMan::end_draw_debug();

};

void ProjectileMan::debug_ui() {


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

IProjectile& ProjectileMan::get_projectile(uint32_t id) {

    for (auto& container : m_projectiles) {

        if (container.id == id) {
            return *container.projectile_ptr;
        }
    }

    throw std::logic_error("Projectile not found");

}

ProjectileMan::Collision ProjectileMan::check_collisions(Rectangle collider, bool colide_foe) {

    auto response = Collision{
        .collided = false,
        .targets = std::list<int32_t>()
    };

    for (auto& container: m_projectiles) {

        if (CheckCollisionRecs(collider, container.projectile_ptr->get_hitbox()) && container.projectile_ptr->is_foe() == colide_foe) {

            response.collided = true;
            response.targets.push_back(container.id);
        }

    }

    return response;

}

