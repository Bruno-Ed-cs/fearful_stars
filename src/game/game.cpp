#include "game.hpp"
#include "asset_man.hpp"
#include "globals.hpp"
#include "raylib.h"

Game::Game() {

    player = actors.activate(Player::make());
    actors.activate(Meteorite::make({200, 100}));
    actors.activate(Meteorite::make({200, 20}));
    actors.activate(Meteorite::make({200, 110}));
    actors.activate(Meteorite::make({200, 50}));
    std::println("player: {}", player);
}


void Game::update() {

    for (int i = actors.begin(); i < actors.end(); i++) {

        if (actors.is_active(i)) {

            switch(actors[i].type) {

                case Actor::Player: { Player::update(i, *this); break; }
                case Actor::Meteorite: { Meteorite::update(i, *this); break; }

            }

        }

    }

    for (int i = enemy_proj.begin(); i < enemy_proj.end(); i++) {

        if (enemy_proj.is_active(i)) {

            switch(enemy_proj[i].type) {
                case Projectile::Plasma: { PlasmaProjectile::update(i, enemy_proj, *this); break; }

            }

            if (!Engine::in_world_bounds(enemy_proj[i].pos.vec(), 50)) {

                enemy_proj.deactivate(i);

            }

        }
    }

    for (int i = player_proj.begin(); i < player_proj.end(); i++) {
        if (player_proj.is_active(i)) {

            switch(player_proj[i].type) {
                case Projectile::Plasma: PlasmaProjectile::update(i, player_proj, *this);

            }

            if (!Engine::in_world_bounds(player_proj[i].pos.vec() ,50)) {

                player_proj.deactivate(i);

            }

        }

    }

    //damage transmission
    for (int i = enemy_proj.begin(); i < enemy_proj.end(); i++) {

        if (enemy_proj.is_active(i) && 
                CheckCollisionRecs(
                   actors[player].hitbox.get(actors[player].pos.vec()), 
                   enemy_proj[i].hitbox.get(enemy_proj[i].pos.vec())
                   )
                ){

            if (enemy_proj[i].damage_output.available()) {

                auto damage = enemy_proj[i].damage_output.extract();
                actors[player].damage_intake.input(damage);
            }
        }

    }

    for (int i = player_proj.begin(); i < player_proj.end(); i++) {

        if (!player_proj.is_active(i)) {
            continue;
        }

        for (int j = actors.begin(); j < actors.end(); j++) {
            if (j != player && actors.is_active(j) && 
                    CheckCollisionRecs(actors[j].hitbox.get(actors[j].pos.vec()), 
                        player_proj[i].hitbox.get(player_proj[i].pos.vec()))) {

                if (player_proj[i].damage_output.available()) {
                    auto damage = player_proj[i].damage_output.extract();
                    actors[j].damage_intake.input(damage);
                    // std::println("transfer: {}", damage);
                }


            }
        }

    }

    // contact damage
    //

    for (int i = actors.begin(); i < actors.end(); i++) {

        if (!actors.is_active(i)) {
            continue;
        }

        if (i == player) {
            continue;
        }

        if (CheckCollisionRecs(actors[i].hitbox.get(actors[i].pos.vec()), actors[player].hitbox.get(actors[player].pos.vec()))) {

            actors[player].damage_intake.input(1); 

        }

    }
}

void Game::draw() {

    for (int i = actors.begin(); i < actors.end(); i++) {

        if (actors.is_active(i)) {

            switch(actors[i].type) {

                case Actor::Player: {
                                        Player::draw(actors[i]);
                                        break;
                                    }

                case Actor::Meteorite: {
                                           Meteorite::draw(actors[i]);
                                           break;
                                       }

            }

        }

    }

    for (int i = enemy_proj.begin(); i < enemy_proj.end(); i++) {

        auto enemy = enemy_proj[i];
        if (enemy_proj.is_active(i) && !enemy.spritesheet.empty()) {

            auto origin = enemy_proj[i].animation.get_frame();
            auto dest = Rectangle{enemy.pos.x, enemy.pos.y, origin.width, origin.height};
            auto sprite = Engine::AssetMan::get_texture(enemy.spritesheet);

            DrawTexturePro(sprite, origin, dest, {0, 0}, 0.0, RED);
        }
    }

    for (int i = player_proj.begin(); i < player_proj.end(); i++) {
        auto proj = player_proj[i];
        if (player_proj.is_active(i) && !proj.spritesheet.empty()) {

            auto origin = player_proj[i].animation.get_frame();
            auto dest = Rectangle{proj.pos.x, proj.pos.y, origin.width, origin.height};
            auto sprite = Engine::AssetMan::get_texture(proj.spritesheet);

            DrawTexturePro(sprite, origin, dest, {0, 0}, 0.0, Color{104, 189, 255, 255});
        }

    }

}
