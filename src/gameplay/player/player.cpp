#include "deps.hpp"
#include "gameplay/projectile/upgrade/upgrade_proj.hpp"
#include "rocksdb/options.h"
#include "saving.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "input_man.hpp"
#include "timer.hpp"
#include "globals.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "player.hpp"
#include "gameplay/components/position.hpp"
#include "render_man.hpp"
#include "systems.hpp"
#include "player.hpp"
#include "primary_shots/shooting_machine.hpp"
#include <string>


using namespace Game;

constexpr void upgrader(Player& player) {
    switch (player.upgrade) {

        case 0:
            break;

        case 1:

            if (player.primary_level >= 3)
                break;

            player.primary_level++;
            player.primary_level = std::clamp(player.primary_level, 1, 3);
            player.upgrade -= 1;

            break;

        case 2:

            if (player.secondary_level >= 2)
                break;

            player.secondary_level++;
            player.secondary_level = std::clamp(player.secondary_level, 0, 2);
            player.upgrade -= 2;

            break;

        case 3:

            if (player.aux_level >= 2)
                break;

            player.aux_level++;
            player.aux_level = std::clamp(player.aux_level, 0, 2);
            player.upgrade -= 3;

            break;

        default:

            player.lives.points++;
            player.upgrade -= 4;

            break;

    }


}

void Player::update(double dt, Engine::GameState& sys) {

    static Engine::Timer press_colldown = Engine::Timer(0.5);
    press_colldown.update(dt);

    Vector2 direction = {0,0};

    if (Engine::InputMan::is_event_active("move_right")) {

        direction.x = 1;

    }

    if (Engine::InputMan::is_event_active("move_up")) {

        direction.y = -1;

    }

    if (Engine::InputMan::is_event_active("move_down")) {

        direction.y = 1;

    }

    if (Engine::InputMan::is_event_active("move_left")) {

        direction.x = -1;

    }

    if (Engine::InputMan::is_event_active("upgrade")) {

        if (press_colldown.past_limit()) {

            press_colldown.reset();
            upgrader(*this);
        }

    }


    primary_shot->run(*this, *sys.projectile, dt);
    secondary_shot->run(*this, sys, dt);
    special_shot->run(*this, sys, dt);
    aux_power->run(*this, sys, dt);

    direction = Vector2Normalize(direction);


    Vector2 movement;


    if (Engine::InputMan::is_event_active("slowdown")) {

        movement = direction * (dt * (speed * 0.6));

    } else {

        movement = direction * (dt * speed);

    }

    //std::println("movement = x{} y{}", movement.x, movement.y);


    pos += movement;

    pos.x = Clamp(pos.x, 0.0, Engine::g_world_size.x);
    pos.y = Clamp(pos.y, 0.0, Engine::g_world_size.y);

    graze_cooldown.update(dt);
    invis_timer.update(dt);

    if (sys.projectile->check_collisions(graze_range.get(pos.vec()), true).collided && graze_cooldown.past_limit()) {

        graze_cooldown.reset();

        special_meter += 2;
        special_meter = std::clamp(special_meter, 0, 100);
    }

    if (invis_timer.past_limit()) 
        invincible = false;

    auto collisions_proj_foe = sys.projectile->check_collisions(hitbox.get(pos.vec()), true);
    auto collisions_proj = sys.projectile->check_collisions(hitbox.get(pos.vec()), false);
    auto collisions_enemy = sys.enemy->check_collisions(hitbox.get(pos.vec()));

    if (collisions_proj_foe.collided ||
        collisions_enemy.has_collided) {

        take_damage();

    }

    if (collisions_proj.collided) {

        for (auto& id : collisions_proj.targets) {

            auto& proj = sys.projectile->get_projectile(id);

            if (proj.get_type() == typeid(UpgradeProj)) {

                upgrade++;
                sys.projectile->append_delete_queue(id);

            }

        }

    }



    if (lives.points == 0) {

        die(sys);

    }


    //std::cout << position.get_round().x << " " << position.get_round().y << " " << direction.x << " " << direction.y <<'\n';
}

void Player::take_damage() {

    if (!invincible) {
        lives.take_damage(1);
        turn_invincible(2);
    }
}

void Player::die(Engine::GameState& sys) {

    dead = true;

}

void Player::revive() {

    lives.restore();
    dead = false;

}

void Player::turn_invincible(double seconds) {

    invincible = true;

    if (seconds < 0)
        return;

    invis_timer = Engine::Timer(seconds);
}

void Player::draw() {


    Rectangle dest{pos.x - 14, pos.y - 8, 26, 16};
    Rectangle origin{0, 0, 26, 16};

    if (invincible) {
        Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle, *spritesheet, dest, origin, 0, 0, RED);

    }
    else Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle, *spritesheet, dest, origin);

}

//Player manager imp

void PlayerMan::update(double dt, Engine::GameState& sys) {

    m_player1->update(dt, sys);
    if (m_player1->dead) {

        //Engine::g_running = false;
        std::println("you died");

    }

}

Player& PlayerMan::get_player() {

    return *m_player1;
}

void PlayerMan::init_player(Vector2 position) {

    m_player1 = std::make_unique<Player>(position);
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

        ImGui::Text("Upgrades");

        if (ImGui::Button("+")) {
            m_player1->upgrade++;

        }

        ImGui::SameLine();
        if (ImGui::Button("-")) {

            m_player1->upgrade--;
        }

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


std::map<std::string, std::string> Player::package() {

    return {
        {"upgrade", std::to_string(upgrade)},
        {"special_meter", std::to_string(special_meter)},
        {"primary_level", std::to_string(primary_level)},
        {"secondary_level", std::to_string(secondary_level)},
        {"aux_level", std::to_string(aux_level)},
        {"lives", std::to_string(lives.points)},
        {"pos_x", std::to_string(pos.x)},
        {"pos_y", std::to_string(pos.y)},

        {"special_shot", "Basic"},
        {"aux_power", "Basic"},
        {"primary_shot", primary_shot->get_name()}
    };

}

void Player::unpack(std::map<std::string, std::string> packed_mem) {

    upgrade = std::stoi(packed_mem["upgrade"]);
    special_meter = std::stoi(packed_mem["special_meter"]);
    primary_level = std::stoi(packed_mem["primary_level"]);
    secondary_level = std::stoi(packed_mem["secondary_level"]);
    aux_level = std::stoi(packed_mem["aux_level"]);
    lives = Health(std::stoi(packed_mem["lives"]));
    pos.y = std::stoi(packed_mem["pos_y"]);
    pos.x = std::stoi(packed_mem["pos_x"]);

    primary_shot.reset(make_shooting_machine(packed_mem["primary_shot"]));

}

void PlayerMan::save_player(Engine::GameState& sys) {

    std::string key;
    std::string value;

    auto members = m_player1->package();

    for (auto& member: members) {

        key = key_encode("Player", 1, 1, member.first);
        value = member.second;

        if (sys.save_slot != 0) {
            sys.save_connection->Put(rocksdb::WriteOptions(), key, value);
        }
    }


}

void PlayerMan::load_player(Engine::GameState& sys) {

    if (sys.save_slot == 0) return;

    std::string value;
    std::map<string, string> package;

    auto* it = sys.save_connection->NewIterator(rocksdb::ReadOptions());

    string prefix = "Player:1:1";

    for (it->Seek(prefix); it->Valid() && it->key().starts_with(prefix); it->Next()) {

        std::println("{} => {}", it->key().ToString(), it->value().ToString());

        std::map<string, string> identity = key_decode(it->key().ToString());

        std::println("identity = {}", identity);
        package.insert({identity["member"], it->value().ToString()});

    }

    std::println("{}", package);

    m_player1->unpack(package);
    delete it;
    
}
