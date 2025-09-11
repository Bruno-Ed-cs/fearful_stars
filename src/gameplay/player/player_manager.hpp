#pragma once

#include "player.hpp"

namespace Game {

class ProjectileMan;
class EnemyMan;

class PlayerMan {

public:

    void update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man);
    void draw();
    Player& get_player();
    void create_player1(Vector2 position);


    void debug();

private:

    Player* m_player1;

};

}
