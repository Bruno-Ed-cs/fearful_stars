#pragma once

#include "deps.hpp"
#include "gameplay/components/position.hpp"

namespace Engine {

template<typename T>
using sptr = std::shared_ptr<T>;

struct BackgroundElement {
    
    Game::Position canva_location;
    sptr<Texture> sprite;
    double rotation;
    double speed;
    std::function<bool(BackgroundElement&, double)> mode;

    struct Mode {

        static bool stay(BackgroundElement&, double dt);
        static bool across(BackgroundElement&, double dt);
        static bool loop(BackgroundElement&, double dt);

    };
};

class BackgroundMan {

    using mode_func = std::function<bool(BackgroundElement&, double)>;

    static uint32_t create_element(sptr<Texture> sprite, Game::Position initial_pos, double speed, double rotation, mode_func mode);
    static void clear_background();
    static void remove_element(uint32_t id);
    static void update(double dt);
    static void draw();

private:

    struct ElementContainer {

        uint32_t id;
        BackgroundElement element;

    };

    inline static std::vector<ElementContainer> element_bank;
};

}
