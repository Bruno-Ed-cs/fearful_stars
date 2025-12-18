#pragma once

#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "globals.hpp"
#include "systems.hpp"
#include "background_man.hpp"
#include "timer.hpp"

void update_loop(double dt, Engine::Systems& sys) {

    static Engine::Timer pause_cooldown {0.5};
    pause_cooldown.update(dt);

    if (Engine::InputMan::is_event_active("pause") && pause_cooldown.past_limit()) {

        pause_cooldown.reset();
        sys.pause = !sys.pause;
    }

    if (!sys.pause) {
        sys.projectile->update(dt, sys);
        sys.enemy->update(dt, sys);
        sys.player->update(dt, sys);
        sys.level->update(sys, dt);
        Engine::BackgroundMan::update(dt);
    }

    sys.ui->update(dt, sys);


}
