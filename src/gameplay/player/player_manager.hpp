#pragma once

#include "gameplay/enemy/enemy_man.hpp"
#include "player.hpp"

namespace Game {

class PlayerMan {

public:

    static void setup();
    static void clean();
    static void update(double dt, EnemyMan& enemy_man);

    static Player& get_player();
    static void debug();

private:

    static Player* s_player;

};

}
