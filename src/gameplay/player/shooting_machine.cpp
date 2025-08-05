#include "shooting_machine.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/player/shooting_state.hpp"
#include "gameplay/projectile/basic_projectile.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "position.hpp"

using namespace game;

void ShootingMachine::run(Player* player) {

    m_running = true;

    while (m_running) {

        auto new_state = m_state->run(player, *this);
        delete m_state;
        m_state = new_state;

    }

}

ShootingState* StateIdle::run(Player* player, ShootingMachine& machine) {

    if(player->m_cooldown.past_limit() && IsKeyDown(KEY_SPACE)) {

        player->m_cooldown.reset();
        return new StateShoot();

    } else {

        machine.exit();
        return new StateIdle();
    }


}

ShootingState* StateShoot::run(Player* player, ShootingMachine& machine) {

    double proj_speed = 200.0f;
    Vector2 direction{1, 0};
    bool foe = false;
    engine::Position pos = player->m_position.get_copy();
    pos.move(Vector2{0, -3});

    ProjectileMan::request_projectile<BasicProjectile>(pos, direction, proj_speed, foe);

    machine.exit();
    return new StateIdle();

}

