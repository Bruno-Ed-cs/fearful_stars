#include "deps.hpp"

#include "player_manager.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "player.hpp"
#include "gameplay/components/position.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"

using namespace Game;

void PlayerMan::update(double dt, Engine::Systems& sys) {

    m_player1->update(dt, sys);

}

Player& PlayerMan::get_player() {

    return *m_player1;
}

void PlayerMan::init_player(Vector2 position) {

    m_player1 = new Player(position);
}


void PlayerMan::debug_ui() {

    ImGui::Begin("Player debug");
    {
        Vector2 position = m_player1->pos.vec();

        ImGui::Text("Position:\nx: %f\ny: %f", position.x, position.y);
        ImGui::Text("Shooting cooldown: %f", m_player1->cooldown.get_time());
    }
    ImGui::End();


}

void PlayerMan::debug_world() {

    Engine::RenderMan::begin_draw_debug();

    DrawCircleV(m_player1->pos.vec(), 1, GREEN);

    Engine::RenderMan::end_draw_debug();

}

void PlayerMan::draw() {

    m_player1->draw();

}
