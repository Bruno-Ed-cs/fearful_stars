#pragma once

#include "entity.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "gameplay/levels/levels.hpp"
#include "gameplay/ui/interfaces/pause_ui.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "systems.hpp"
#include "background_man.hpp"
#include "timer.hpp"
#include <print>

void update_loop(double dt, Engine::Systems& sys) {

    if (Engine::InputMan::is_event_active("pause") && !sys.pause) {

        sys.ui->stack_interface(std::make_unique<Game::PauseUi>());
        //std::println("game paused");
    }

    if (!sys.pause) {
        //sys.projectile->update(dt, sys);
        //sys.enemy->update(dt, sys);
        //sys.player->update(dt, sys);
        //sys.level->update(sys, dt);
        Engine::BackgroundMan::update(dt);
        
        for (auto& entity: sys.entity.data) {

            entity->update(dt, sys);
        }
    }

    sys.ui->update(dt, sys);
}
