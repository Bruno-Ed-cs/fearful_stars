#include "background_man.hpp"
#include "render_man.hpp"

using namespace Engine;

uint32_t BackgroundMan::create_element(sptr<Texture> sprite, Game::Position initial_pos, double speed, double rotation, mode_func mode) {

}

void BackgroundMan::clear_background() {

}

void BackgroundMan::remove_element(uint32_t id) {

    for (int i = 0; i < element_bank.size(); ++i) {

        if (element_bank[i].id == id) {

            element_bank.erase(element_bank.begin() + i);

        }

    }

}

void BackgroundMan::update(double dt) {

    static std::vector<bool> element_status;
    element_status.reserve(element_bank.size());

    for (auto& container : element_bank) {

        element_status.push_back(container.element.mode(container.element, dt));
    }

    for (int i = 0; i < element_status.size(); ++i) {

        if (element_status[i] == false) {

            remove_element(element_bank[i].id);
        }

    }

    element_status.clear();
}

void BackgroundMan::draw() {

    for (auto& container : element_bank) {


    }

}



bool BackgroundElement::Mode::stay(BackgroundElement&, double dt) {

}

bool BackgroundElement::Mode::across(BackgroundElement&, double dt) {

}

bool BackgroundElement::Mode::loop(BackgroundElement&, double dt) {

}
