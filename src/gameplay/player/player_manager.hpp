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
    void init_player(Vector2 position);


    void debug_ui();
    void debug_world();

private:

    Player* m_player1;

};

}
