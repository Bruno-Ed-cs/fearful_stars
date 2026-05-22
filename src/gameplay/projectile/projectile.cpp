#include "deps.hpp"

#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/projectile/big_shot/bigshot_proj.hpp"
#include "gameplay/projectile/missile/missile_proj.hpp"
#include "gameplay/projectile/orbital/orbital_proj.hpp"
#include "gameplay/projectile/plasma/plasma.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "projectile.hpp"
#include "basic/basic_projectile.hpp"
#include "rocksdb/iterator.h"
#include "rocksdb/options.h"
#include "saving.hpp"
#include "globals.hpp"
#include "imgui.h"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"

using namespace Game;

//CollisionRes ProjectileMan::check_collision(Rectangle target) {

//}

void ProjectileMan::update(double dt, Engine::GameState& sys) {

    //    std::cout << "update\n" << m_projectiles.size() << '\n';


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
            if (cur_proj.projectile_ptr != nullptr) {
                auto pos = cur_proj.projectile_ptr->get_position();

                if (!CheckCollisionRecs(cur_proj.projectile_ptr->get_hitbox(), 
                            Rectangle{ .x = 0, .y = 0, .width = Engine::g_world_size.x, .height = Engine::g_world_size.y})) {

                    cur_proj.active = false;
                    cur_proj.deadtime.reset();
                }
            }

        } else {

            cur_proj.deadtime.update(dt);

            if (cur_proj.deadtime.past_limit()) {

                m_projectiles.erase(m_projectiles.begin() + i);
            }
        }

    }


    for (auto& container: m_projectiles) {

        if (container.projectile_ptr->destroy_self() && container.active) {

            append_delete_queue(container.id);

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

uint32_t ProjectileMan::get_id(Projectile* target) {

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

Projectile& ProjectileMan::get_projectile(uint32_t id) {

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

        if (CheckCollisionRecs(collider, container.projectile_ptr->get_hitbox()) && container.projectile_ptr->is_foe() == colide_foe && container.active) {

            response.collided = true;
            response.targets.push_back(container.id);
        }

    }

    return response;

}

bool ProjectileMan::exists(uint32_t id) {

    for (auto& container : m_projectiles) {

        if (container.id == id && container.active) {

            return true;
        }

    }

    return false;



}

void ProjectileMan::save_projectiles(Engine::GameState& sys) {

    if (sys.save_slot == 0) return;

    rocksdb::Iterator* it = sys.save_connection->NewIterator(rocksdb::ReadOptions());

    for (it->Seek("Projectile"); it->Valid() && it->key().starts_with("Projectile"); it->Next()) {

        sys.save_connection->Delete(rocksdb::WriteOptions(), it->key());
    }

    for (auto& container : m_projectiles) {

        if (container.active) {

            Engine::Package members = container.projectile_ptr->package();
            std::string key;
            std::string value;

            for (auto& member: members) {
                key = key_encode("Projectile", (int)container.projectile_ptr->get_type(), container.id, member.first);
                value = member.second;

                sys.save_connection->Put(rocksdb::WriteOptions(), key, value);
            }

        }

    }
}


Projectile* ProjectileMan::make_projectile(ProjectileType type) {

    Projectile* proj = nullptr;

    switch (type) {

        case ProjectileType::Basic:
            proj = new BasicProjectile();
        break;

        case ProjectileType::Upgrade:
            proj = new UpgradeProj();
        break;

        case ProjectileType::BigShot:
            proj = new BigShotProj();
        break;

        case ProjectileType::Missile:
            proj = new MissileProj();
        break;

        case ProjectileType::Orbital:
            proj = new OrbitalProj();
        break;

        case ProjectileType::Plasma:
            proj = new PlasmaProj();
        break;

        default:
            proj = new BasicProjectile();
        break;

    }

    return proj;
}

void ProjectileMan::load_projectiles(Engine::GameState& sys) {
    using subtype = uint32_t;
    using id = uint32_t;
    if (sys.save_slot == 0) return;

    m_projectiles.clear();

    // get all the unique entries
    std::vector<std::tuple<subtype, id>> identifiers;
    identifiers.reserve(50);

    rocksdb::Iterator* it = sys.save_connection->NewIterator(rocksdb::ReadOptions());

    for (it->Seek("Projectile"); it->Valid() && it->key().starts_with("Projectile"); it->Next()) {
        
        bool exist = false;
        auto parsed_key = key_decode(it->key().ToString());

        for (int i = 0; i < identifiers.size(); ++i) {


            if (std::stoi(parsed_key["id"]) == std::get<1>(identifiers[i])) {

                exist = true;
                break;
            }

        }

        if (!exist) {
            identifiers.push_back({std::stoi(parsed_key["subtype"]), std::stoi(parsed_key["id"])});
        }

    }

    it->Reset();
    // create and umpack the projectiles

    for (auto& identity: identifiers) {

        std::string prefix = std::format("Projectile:{}:{}", std::get<0>(identity), std::get<1>(identity));
        Engine::Package packed_proj;

        for (it->Seek(prefix); it->Valid() && it->key().starts_with(prefix); it->Next()) {
            
            auto parsed_key = key_decode(it->key().ToString());

            packed_proj.insert({parsed_key["member"], it->value().ToString()});

        }

        Projectile* proj = make_projectile((ProjectileType)std::get<0>(identity));

        proj->unpack(packed_proj);

        ProjectileMan::ProjContainer capsule = {
            .projectile_ptr = std::unique_ptr<Projectile>(proj),
            .active = true,
            .id = std::get<1>(identity),
        };

        m_projectiles.push_back(std::move(capsule));
    }
}

