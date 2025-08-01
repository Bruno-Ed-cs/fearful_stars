#pragma once

#include "player.hpp"

namespace game {

class PlayerMan {

public:

    static void setup();
    static void clean();
    static void update(double dt);

    static Player& get_player();

private:

    static Player s_player;

};

}
