#include "game.hpp"
#include "raylib.h"


Actor Meteorite::make(Position pos) {

    auto meteorite = Actor();

    meteorite.type = Actor::Meteorite;
    meteorite.dir = Direction{-1, 0};
    meteorite.speed = 15;
    meteorite.pos = pos;
    meteorite.hitbox = Hitbox{28, 22};
    meteorite.spritesheet = "meteorite";

    return meteorite;

}

void Meteorite::update(idx self, Game& gm) {

    auto& meteorite = gm.actors[self];

    double dt = GetFrameTime();
    Vector2 movement = Vector2Normalize(meteorite.dir.vec()) * dt * meteorite.speed;
    meteorite.pos += movement;

    if (meteorite.lives.is_dead()){

        gm.actors.deactivate(self);
    }
}

void Meteorite::draw(Actor& meteorite) {

    Rectangle sorce = Rectangle{0, 0, meteorite.hitbox.width, meteorite.hitbox.height};
    Texture2D sprite = Engine::AssetMan::get_texture(meteorite.spritesheet);
    DrawTexturePro(
            sprite,
            sorce,
            meteorite.hitbox.get(meteorite.pos.vec()),
            {0, 0},
            0.0,
            WHITE);
}

