#pragma once

#include "gameplay/entity.hpp"
#include "gameplay/projectile.hpp"
#include <memory>
#include <vector>
namespace game {

    inline std::vector<std::unique_ptr<Entity>> g_bullets;

}
