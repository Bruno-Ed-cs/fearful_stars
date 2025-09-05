#include "deps.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"

#include "basic_projectile.hpp"

using namespace Game;

void BasicProjectile::update(double dt, EnemyMan& enemy_man) {

    Vector2 movement = m_direction * m_speed * dt;

    m_pos += movement;

    m_hitbox.x = m_pos.x;
    m_hitbox.y = m_pos.y;

    if (!m_foe) {

        EnemyCollision collision = enemy_man.check_collisions(m_hitbox);

        if (collision.has_collided) {

            enemy_man.trigger_event(collision.enemy_id, EnemyEvent::take_damage, enemy_man);

            uint32_t id = ProjectileMan::get_id(this);
            ProjectileMan::append_delete_queue(id);


        }


    } 

//    std::cout << m_pos.get_real().x << " " << m_pos.get_real().y << '\n';
}

void BasicProjectile::draw() {

    DrawRectangleRec(m_hitbox, BLUE);

}
