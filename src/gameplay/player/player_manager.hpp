#pragma once

#include "player.hpp"
#include "systems.hpp"

namespace Game {

class ProjectileMan;
class EnemyMan;

class PlayerMan {

public:

    void update(double dt, Engine::Systems& sys);
    void draw();
    Player& get_player();
    void create_player1(Vector2 position);


    void debug();

private:

    Player* m_player1;

};

}
