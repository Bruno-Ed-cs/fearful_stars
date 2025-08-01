#pragma once

#include "gameplay/player.hpp"

namespace game {

class PlayerManager {

public:

    static void setup();
    static void clean();
    static void update(double dt);

    static Player& get_player();

private:

    static Player s_player;

};

}
