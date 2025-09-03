#pragma once

namespace Game {
    class EnemyMan;
}

namespace Engine {

class IEntity {

public:

    virtual ~IEntity() = default;

    virtual void update(double dt, Game::EnemyMan& enemy_man) = 0;
    virtual void draw() = 0;


};

}
