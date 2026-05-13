#pragma once
#include "gameplay/levels/action.hpp"
#include "systems.hpp"
#include "background_man.hpp"
#include "asset_man.hpp"

template <typename T>
using sptr = std::shared_ptr<T>;

namespace Game {

class SetBackgroundAction : public Action {


public:

    std::string bg_name;
    SetBackgroundAction(std::string background):
    bg_name(background){}

    void restart() override {


    }

    bool execute(Engine::GameState& sys, double dt) override {

        sptr<Texture> bg = Engine::AssetMan::get_texture(bg_name);

        std::println("{}", bg_name);

        //std::println("cur time = {}", timer.get_time());
        //
        Engine::BackgroundMan::create_element(bg,
                Rectangle{0, 0, (float)bg->width, (float)bg->height},
                Rectangle{0, 0, (float)bg->width, (float)bg->height},
                Game::Position{0, 0},
                0,
                0,
                -1, 
                Engine::BackgroundElement::Mode::stay);

        return true;

    };

};

}
