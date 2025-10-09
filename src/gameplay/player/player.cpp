#include "deps.hpp"
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

    Position& position = components.get<Position>();

    position += movement;

    position.x = Clamp(position.x, 0.0, Engine::g_canva_size.x);
    position.y = Clamp(position.y, 0.0, Engine::g_canva_size.y);

    //std::cout << position.get_round().x << " " << position.get_round().y << " " << direction.x << " " << direction.y <<'\n';
}

void Player::draw() {

    Position& pos = components.get<Position>();

    Rectangle dest{pos.x - 8, pos.y - 8, 16.0f, 16};
    Rectangle origin{3 * 16, 0, -16, 16};
    DrawTexturePro(*Assets::ship_tilemap, origin , dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawCircleV(pos.vec(), 1.0f, GREEN);
    DrawCircleV(pos.vec(), 0.5f, GRAY);

}
