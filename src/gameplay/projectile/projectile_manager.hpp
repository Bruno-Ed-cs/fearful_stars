#pragma once 

#include "deps.hpp"
#include "projectile.hpp"

namespace game {

enum struct ProjType {

   basic
};

struct CollisionRes {

    bool collided;
    Projectile& projectile;
};

class ProjectileMan {

public:

    static void request_projectile(ProjType type, Vector2 direction, double speed, bool foe);
    static CollisionRes check_collision(Rectangle target);
    static void update(double dt);
    static void draw();

private: 

    static std::vector<std::unique_ptr<Projectile>> s_projectiles;

};


}
