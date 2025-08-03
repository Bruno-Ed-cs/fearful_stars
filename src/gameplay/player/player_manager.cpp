#include "deps.hpp"

#include "player_manager.hpp"
#include "player.hpp"

using namespace game;

game::Player* PlayerMan::s_player;

void PlayerMan::setup() {

    s_player = new Player(Vector2{0, 0});

}

void PlayerMan::clean() {}
void PlayerMan::update(double dt) {

    s_player->update(dt);

}

Player& PlayerMan::get_player() {

    return *s_player;
}
