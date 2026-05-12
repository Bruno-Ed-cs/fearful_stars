    
#include "big_shooter.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/big_shot/bigshot_proj.hpp"
#include "input_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

using namespace Game;

void BigShooter::run(Player& player, Engine::Systems& sys, double dt) {

    if (player.special_meter >= 100 && Engine::InputMan::is_event_active("special")) {

        std::println("booom");
        sys.projectile->emplace<BigShotProj>(player.pos.vec(), Vector2{1, 0}, 100, false);
        player.special_meter = 0;

    }

}

