#include "missile_shooter.hpp"
#include "gameplay/projectile/missile/missile_proj.hpp"
#include "input_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"


using namespace Game;

void MissileShooter::run(Player& player, Engine::Systems& sys, double dt) {

    cooldown.update(dt);

    if (Engine::InputMan::is_event_active("shoot") && cooldown.past_limit()) {

        switch (player.secondary_level) {

            case 1:

                sys.projectile->request_projectile<MissileProj>(player.pos.vec(), Vector2{0, 1}, 150, false);
                break;

            case 2:

                sys.projectile->request_projectile<MissileProj>(player.pos.vec(), Vector2{0, 1}, 150, false);
                sys.projectile->request_projectile<MissileProj>(player.pos.vec(), Vector2{0, -1}, 150, false);

                break;

            default:
                break;

        }

        cooldown.reset();

    }

}
