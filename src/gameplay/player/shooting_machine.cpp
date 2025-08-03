#include "shooting_machine.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/player/shooting_state.hpp"
#include "gameplay/projectile/basic_projectile.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

using namespace game;

void ShootingMachine::run(Player* player) {

    auto new_state = m_state->run(player);
    delete m_state;
    m_state = new_state;

}

ShootingState* StateIdle::run(Player* player) {

    if(player->m_cooldown.past_limit() && IsKeyDown(KEY_SPACE)) {

        player->m_cooldown.reset();
        return new StateShoot();

    } else {

        return new StateIdle();
    }


}

ShootingState* StateShoot::run(Player* player) {

    double proj_speed = 200.0f;
    Vector2 direction{1, 0};
    bool foe = false;

    ProjectileMan::request_projectile<BasicProjectile>(player->m_position,
                                                       direction,
                                                       proj_speed,
                                                       foe);

    return new StateIdle();

}

