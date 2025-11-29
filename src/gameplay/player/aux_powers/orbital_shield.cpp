#include "gameplay/projectile/orbital/orbital_proj.hpp"
#include "systems.hpp"
#include "orbital_shield.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "deps.hpp"
#include <memory>

using namespace Game;

void OrbitalShield::run(Player& player, Engine::Systems& sys, double dt) {

    static bool place_orb1 = false;

    switch (player.aux_level) {

        case 1:
            if (!place_orb1) {

                orb1 = sys.projectile->request_projectile<OrbitalProj>(player.pos.vec(), Vector2{1,1} , 100, false);
            }
        break;

        case 2:
        break;

        default:
        break;
    
    }



}


