#include "gameplay/player/primary_shots/basic_shot.hpp"
#include "deps.hpp"

#include "shooting_machine.hpp"
#include "gameplay/player/player.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "input_man.hpp"
#include "raylib.h"

using namespace Game;

void BasicShot::run(Player* player, ProjectileMan& projectile_man) {

    m_running = true;
     

    while (m_running) {

        auto& state = *m_state_collection[m_state];

        state.run(player, *this, projectile_man);
        bool has_transitioned = state.transition(player, *this, projectile_man);
        
        //std::println("loop is {}", m_running);

        if (state.is_final() || !has_transitioned) {
            transition_to(m_initial_state);
            m_running = false;
        }
    }
}

void BasicShot::transition_to(const std::string& state_name) {

    if (!m_state_collection.contains(state_name))
        throw std::logic_error("There is no state such as: " + state_name);

    m_state = state_name;

}

void StateIdle::run(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) {

    return;

}

bool StateIdle::transition(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) {

    if(player->cooldown.past_limit() && Engine::InputMan::is_event_active("shoot")) {

        player->cooldown.reset();
        machine.transition_to("Shoot");
        return true;

    } 

    return false;

}

void StateShoot::run(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) {

    double proj_speed = 200.0f;
    Vector2 direction{1, 0};
    bool foe = false;
    Vector2 pos = player->pos.vec();
    pos += Vector2{0, -3};

    projectile_man.request_projectile<BasicProjectile>(pos, direction, proj_speed, foe);
    PlaySound(*player->shooting_sound);
}

bool StateShoot::transition(Player* player, ShootingMachine& machine, ProjectileMan& projectile_man) {

    return false;

}

