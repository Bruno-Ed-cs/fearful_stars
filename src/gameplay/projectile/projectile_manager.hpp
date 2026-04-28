#pragma once 

#include "deps.hpp"
#include "entity.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player.hpp"
#include "projectile.hpp"
#include "id_generator.hpp"
#include "systems.hpp"
#include "timer.hpp"
#include <memory>

namespace Game {

template <typename T>
concept is_projectile = std::is_base_of_v<Projectile, T> && std::is_default_constructible_v<T>;

struct ProjectileMan {

    static std::vector<size_t> get_colliding_entities(ComponentMan& comp, Rectangle target, bool foe);
    static int get_damage(ComponentMan& comp, size_t projectile);

};
}
