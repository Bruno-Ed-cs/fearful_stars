#include "shooting_machine.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/player/shooting_state.hpp"
#include "gameplay/projectile/basic_projectile.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "input_man.hpp"
#include "position.hpp"

using namespace game;

void ShootingMachine::run(Player* player) {

    m_running = true;
     

    while (m_running) {

        auto& state = *m_state_collection[m_state];
        std::string prev_state = m_state;

        state.run(player, *this);

        if (state.is_final() || m_state == prev_state) {
            transition_to(m_initial_state);
            m_running = false;
        }
    }
}

void ShootingMachine::transition_to(const std::string& state_name) {

    if (!m_state_collection.contains(state_name))
        throw std::logic_error("There is no state such as: " + state_name);

    m_state = state_name;

}

void StateIdle::run(Player* player, ShootingMachine& machine) {

    if(player->m_cooldown.past_limit() && engine::InputMan::is_event_active("shoot")) {

        player->m_cooldown.reset();
        machine.transition_to("Shoot");

    } 

}

void StateShoot::run(Player* player, ShootingMachine& machine) {

    double proj_speed = 200.0f;
    Vector2 direction{1, 0};
    bool foe = false;
    engine::Position pos = player->m_position;
    pos.move(Vector2{0, -3});

    ProjectileMan::request_projectile<BasicProjectile>(pos, direction, proj_speed, foe);

    machine.transition_to("Idle");

}

