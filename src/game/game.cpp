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

    for (int i = 1; i < actors.size(); i++) {

        if (actors.active(i)) {

            switch(actors[i].type) {

                case Actor::Player: {
                        Player::update(i, *this);
                        break;
                }

                case Actor::Meteorite: {
                        Meteorite::update(i, *this);
                        break;
                }

            }

        }

    }

    for (int i = 1; i < max_projectiles; i++) {

        if (enemy_proj.active(i)) {

            switch(enemy_proj[i].type) {
                case Projectile::Plasma: PlasmaProjectile::update(i, *this, true);

            }

            if (!Engine::in_world_bounds(enemy_proj[i].pos.vec(), 50)) {

                enemy_proj.deactivate(i);

            }

        }


        if (player_proj.active(i)) {

            switch(player_proj[i].type) {
                case Projectile::Plasma: PlasmaProjectile::update(i, *this, false);

            }

            if (!Engine::in_world_bounds(player_proj[i].pos.vec() ,50)) {

                player_proj.deactivate(i);

            }

        }

    }

    //damage transmission
    for (int i = 0; i < enemy_proj.size(); i++) {

        if (enemy_proj.active(i) && 
            CheckCollisionRecs(actors[player].hitbox.get(actors[player].pos.vec()), 
                enemy_proj[i].hitbox.get(enemy_proj[i].pos.vec()))) {

            if (enemy_proj[i].damage_output > 0) {
                actors[player].damage_intake += enemy_proj[i].base_damage;
                enemy_proj[i].damage_output -= enemy_proj[i].base_damage;
            }


        }

    }

    for (int i = 0; i < player_proj.size(); i++) {

        if (!player_proj.active(i)) {
            continue;
        }

        for (int j = 0; j < actors.size(); j++) {
            if (j != player && actors.active(j) && 
                    CheckCollisionRecs(actors[j].hitbox.get(actors[j].pos.vec()), 
                        player_proj[i].hitbox.get(player_proj[i].pos.vec()))) {

                if (player_proj[i].damage_output > 0) {
                    actors[j].damage_intake += player_proj[i].base_damage;
                    player_proj[i].damage_output -= player_proj[i].base_damage;
                }


            }
        }

    }
}

void Game::draw() {

    for (int i = 1; i < actors.size(); i++) {

        if (actors.active(i)) {

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

    for (int i = 1; i < enemy_proj.size(); i++) {

        auto enemy = enemy_proj[i];
        if (enemy_proj.active(i) && !enemy.spritesheet.empty()) {

            auto origin = enemy_proj[i].animation.get_frame();
            auto dest = Rectangle{enemy.pos.x, enemy.pos.y, origin.width, origin.height};
            auto sprite = Engine::AssetMan::get_texture(enemy.spritesheet);

            DrawTexturePro(sprite, origin, dest, {0, 0}, 0.0, RED);
        }


        auto proj = player_proj[i];
        if (player_proj.active(i) && !proj.spritesheet.empty()) {

            auto origin = player_proj[i].animation.get_frame();
            auto dest = Rectangle{proj.pos.x, proj.pos.y, origin.width, origin.height};
            auto sprite = Engine::AssetMan::get_texture(proj.spritesheet);

            DrawTexturePro(sprite, origin, dest, {0, 0}, 0.0, Color{104, 189, 255, 255});
        }

    }

}
