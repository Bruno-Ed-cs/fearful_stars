#include "basic_enemy.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "globals.hpp"
#include "raymath.h"
#include "gameplay/player/player_manager.hpp"

using namespace Game;


void BasicEnemy::draw() {

    DrawRectangleRec(m_hitbox, YELLOW);
};

void BasicEnemy::update(double dt, EnemyMan& enemy_man) {

    m_hitbox.x = m_position.x - m_hitbox.width/2;
    m_hitbox.y = m_position.y - m_hitbox.height/2;

    Player& player = PlayerMan::get_player();
    if (Vector2Distance(player.m_position, m_position) > 50){
        if (m_direction == Vector2{0,1} && m_position.y > Engine::g_canva_size.y) 
            m_direction = Vector2{0, -1};

        if (m_direction == Vector2{0,-1} && m_position.y < 0) 
            m_direction = Vector2{0, 1};

        Vector2 movement = m_direction * m_speed;
        movement = Vector2Normalize(movement);
        m_position += movement;

    } else {


        m_position = Vector2MoveTowards(m_position, player.m_position, m_speed);
    }
};

void BasicEnemy::take_damage(EnemyMan& enemy_man) {

    uint32_t id = enemy_man.get_enemy(this);

    enemy_man.append_delete_queue(id);

}

void BasicEnemy::reset(Vector2 position) {

    m_position = position;

};


