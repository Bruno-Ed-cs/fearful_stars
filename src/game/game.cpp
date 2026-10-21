#include "game.hpp"

Game::Game() {

    player = actors.activate(Player::make());
    std::println("player: {}", player);
}

void Game::update() {

    for (int i = 1; i < actors.m_data.size(); i++) {

        if (actors.m_meta[i]) {

            switch(actors[i].type) {

                case Actor::Player: {
                        Player::update(actors[i]);
                }

            }

        }

    }

}

void Game::draw() {

    for (int i = 1; i < actors.m_data.size(); i++) {

        if (actors.m_meta[i]) {

            switch(actors[i].type) {

                case Actor::Player: {
                        Player::draw(actors[i]);
                }

            }

        }

    }
}
