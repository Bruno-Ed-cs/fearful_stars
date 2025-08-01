#include "deps.hpp"

#include "player_manager.hpp"
#include "player.hpp"

using namespace game;

game::Player PlayerManager::s_player;

void PlayerManager::setup() {

    s_player = Player(Vector2{0, 0});

}

void PlayerManager::clean() {}
void PlayerManager::update(double dt) {

    s_player.update(dt);

}

Player& PlayerManager::get_player() {

    return s_player;
}
