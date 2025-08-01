#include "gameplay/player_manager.hpp"
#include "loops.hpp"
#include "globals.hpp"

void engine::update_loop(double dt) {

    for (int i = 0; i < engine::g_bullets.size(); i++) {

        engine::g_bullets[i]->update(dt);

    }

    game::PlayerManager::update(dt);

}
