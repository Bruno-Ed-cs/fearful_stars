#include "game.hpp"
#include "asset_man.hpp"
#include "globals.hpp"
#include "raylib.h"

Game::Game() {

    player = actors.activate(Player::make());
    std::println("player: {}", player);
}

void Game::update() {

    for (int i = 1; i < actors.size(); i++) {

        if (actors.active(i)) {

            switch(actors[i].type) {

                case Actor::Player: {
                        Player::update(actors[i], *this);
                }

            }

        }

    }

    for (int i = 1; i < max_projectiles; i++) {

        if (enemy_proj.active(i)) {

            switch(enemy_proj[i].type) {
                case Projectile::Plasma: PlasmaProjectile::update(enemy_proj[i], *this);

            }

            if (!Engine::in_world_bounds(enemy_proj[i].pos.vec(), 50)) {

                enemy_proj.deactivate(i);

            }

        }


        if (player_proj.active(i)) {

            switch(player_proj[i].type) {
                case Projectile::Plasma: PlasmaProjectile::update(player_proj[i], *this);

            }

            if (!Engine::in_world_bounds(player_proj[i].pos.vec() ,50)) {

                player_proj.deactivate(i);

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
