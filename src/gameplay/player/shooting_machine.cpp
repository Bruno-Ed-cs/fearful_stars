#include "deps.hpp"

#include "shooting_machine.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/player/shooting_state.hpp"
#include "gameplay/projectile/basic_projectile.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "input_man.hpp"

using namespace game;

void ShootingMachine::run(Player* player) {

    m_running = true;
     

    while (m_running) {

        auto& state = *m_state_collection[m_state];

        state.run(player, *this);
        bool has_transitioned = state.transition(player, *this);
        
        //std::println("loop is {}", m_running);

        if (state.is_final() || !has_transitioned) {
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

    return;

}

bool StateIdle::transition(Player* player, ShootingMachine& machine) {

    if(player->m_cooldown.past_limit() && engine::InputMan::is_event_active("shoot")) {

        player->m_cooldown.reset();
        machine.transition_to("Shoot");
        return true;

    } 

    return false;

}

void StateShoot::run(Player* player, ShootingMachine& machine) {

    double proj_speed = 200.0f;
    Vector2 direction{1, 0};
    bool foe = false;
    Vector2 pos = player->m_position;
    pos += Vector2{0, -3};


    ProjectileMan::request_projectile<BasicProjectile>(pos, direction, proj_speed, foe);
}

bool StateShoot::transition(Player* player, ShootingMachine& machine) {

    return false;

}

