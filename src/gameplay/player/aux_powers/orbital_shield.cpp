#include "gameplay/projectile/orbital/orbital_proj.hpp"
#include "systems.hpp"
#include "orbital_shield.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "deps.hpp"
#include <memory>

using namespace Game;

void OrbitalShield::run(Player& player, Engine::Systems& sys, double dt) {


    switch (player.aux_level) {

        case 1:
            if (!sys.projectile->exists(orb1)) {

                orb1 = sys.projectile->emplace<OrbitalProj>(player.pos.vec(), Vector2{1,1} , 100, false);
            }
        break;

        case 2:

            if (!sys.projectile->exists(orb1)) {

                orb1 = sys.projectile->emplace<OrbitalProj>(player.pos.vec(), Vector2{1,1} , 100, false);
            }


            if (!sys.projectile->exists(orb2)) {

                orb2 = sys.projectile->emplace<OrbitalProj>(player.pos.vec(), Vector2{1,-1} , 100, false);
            }

        break;

        default:
        break;
    
    }



}


