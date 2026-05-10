#include "deps.hpp"

#include "gameplay/projectile/projectile.hpp"
#include "projectile_manager.hpp"
//#include "basic/basic_projectile.hpp"
#include "imgui.h"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include <optional>

using namespace Game;
using indexes = std::vector<size_t>;

//CollisionRes ProjectileMan::check_collision(Rectangle target) {

struct ProjectileMan {

    static indexes get_colliding_entities(ComponentMan& comp, Rectangle target, bool foe) {
        indexes result;
        result.reserve(comp.projectile_tag.data.size());

        for (auto& proj : comp.projectile_tag.data) {

            if (proj.is_foe == foe) {

                size_t entity = *proj.entity_owner;
                auto hitboxes = comp.hitbox.querry_by_owner(entity);

                for (auto& hitbox_id : hitboxes) {

                    Hitbox& hitbox = comp.hitbox[hitbox_id];

                    if(!hitbox.position_link) continue;

                    Position& pos = comp.position[hitbox.position_link.value()];

                    if (CheckCollisionRecs(target, hitbox.get(pos.vec())))
                        result.push_back(*hitbox.entity_owner);
                    }

            }

        }

        return result;

    }

    static std::optional<size_t> get_damage(ComponentMan& comp, size_t projectile) {
        
        auto projectile_damages = comp.damage.querry_by_owner(projectile);

        if (projectile_damages.empty()) return std::nullopt;

        return projectile_damages.front();
    }
};

//}

