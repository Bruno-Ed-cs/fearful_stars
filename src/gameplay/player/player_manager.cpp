#include "deps.hpp"

#include "player_manager.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "player.hpp"
#include "gameplay/components/position.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include <print>

using namespace Game;

void PlayerMan::update(double dt, Engine::Systems& sys) {

    m_player1->update(dt, sys);
    if (m_player1->dead) {

        CloseWindow();
        std::println("you died");

    }

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
        ImGui::Text("Special meter: %d", m_player1->special_meter);
        ImGui::Text("Lives: %d", m_player1->lives.points);
        ImGui::Text("Dead: %d", m_player1->dead);
        ImGui::Text("Upgrades: %d", m_player1->upgrade);

        if (ImGui::Button("Revive")) {

            m_player1->revive();

        }

        if (ImGui::Button("Fill special")) {

            m_player1->special_meter = 100;

        }



        ImGui::Text("Primary level");
        ImGui::SliderInt("Lv##1", &m_player1->primary_level, 1, 3, "%d");

        ImGui::Text("Secondary Level");
        ImGui::SliderInt("Lv##2", &m_player1->secondary_level, 0, 2, "%d");


        ImGui::Text("Aux Level");
        ImGui::SliderInt("Lv##3", &m_player1->aux_level, 0, 2, "%d");

    }
    ImGui::End();


}

void PlayerMan::debug_world() {

    Engine::RenderMan::begin_draw_debug();

    DrawRectangleLinesEx(m_player1->hitbox.get(m_player1->pos.vec()), 1.0, RED);
    DrawRectangleLinesEx(m_player1->graze_range.get(m_player1->pos.vec()), 1.0, GREEN);
    DrawCircleV(m_player1->pos.vec(), 1, GREEN);

    Engine::RenderMan::end_draw_debug();

}

void PlayerMan::draw() {

    m_player1->draw();

}
