#include "component.hpp"
#include "deps.hpp"
#include "render_man.hpp"
#include "systems.hpp"

#include "player.hpp"


using namespace Game;

void Player::update(double dt, Engine::Systems& sys) {

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

    shooting_machine.run(this, *sys.projectile);

    cooldown.update(dt);


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

    //std::cout << position.get_round().x << " " << position.get_round().y << " " << direction.x << " " << direction.y <<'\n';
}

void Player::draw() {


    Rectangle dest{pos.x - 12, pos.y - 8, 24.0f, 16};
    Rectangle origin{0, 0, 24, 16};

    Engine::RenderMan::send_texture(Engine::RenderMan::Plane::middle, *spritesheet, dest, origin);
}

Engine::ComponentContainer Player::get_components() { 

    return Engine::ComponentContainer{&pos, &hitbox, &dir, &hp};

};
