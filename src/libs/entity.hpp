#pragma once


namespace Game {
    class EnemyMan;
    class ProjectileMan;
    class PlayerMan;
}

namespace Engine {

class IEntity {

public:

    virtual ~IEntity() = default;

    virtual void update(double dt, Game::EnemyMan& enemy_man, Game::ProjectileMan& projectile_man, Game::PlayerMan& player_man) = 0;
    virtual void draw() = 0;


};

}
