#include "deps.hpp"

#include "player_manager.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "player.hpp"

using namespace Game;

void PlayerMan::update(double dt, EnemyMan& enemy_man, ProjectileMan& projectile_man ) {

    m_player1->update(dt, enemy_man, projectile_man, *this);

}

Player& PlayerMan::get_player() {

    return *m_player1;
}

void PlayerMan::create_player1(Vector2 position) {

    m_player1 = new Player(position);
}


void PlayerMan::debug() {

    ImGui::Begin("Player debug");
    {
        ImGui::Text("Position:\nx: %f\ny: %f", m_player1->position.x, m_player1->position.y);
        ImGui::Text("Shooting cooldown: %f", m_player1->cooldown.get_time());
    }
    ImGui::End();


}

void PlayerMan::draw() {

    m_player1->draw();

}
