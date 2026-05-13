#include "upgrade_proj.hpp"
#include "render_man.hpp"
#include "gameplay/player/player.hpp"
#include "raylib.h"


using namespace Game;

void UpgradeProj::update(double dt, Engine::GameState& sys) {

    Vector2 movement = Vector2Normalize(orientation.vec()) * (speed * dt);

    pos += movement;

}

void UpgradeProj::draw() {
    
    Rectangle source = Rectangle{0, 0, 16, 16};
    Rectangle view = Rectangle{pos.x - 8, pos.y -8, 16, 16};

    Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle,
                                    *sprite,
                                    view,
                                    source,
                                    0,
                                    0,
                                    WHITE);



}

void UpgradeProj::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {

    this->pos = pos;
    this->speed = speed;
    this->orientation = direction;
    this->foe = foe;
    this->damage = (damage == 0)? this->damage : damage;
    this->destruct = false;

}

