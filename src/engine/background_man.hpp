#pragma once

#include "deps.hpp"
#include "gameplay/components/position.hpp"

namespace Engine {

template<typename T>
using sptr = std::shared_ptr<T>;

struct BackgroundElement {
    
    Game::Position canva_location;
    sptr<Texture> sprite;
    Rectangle source;
    Rectangle projection;
    double rotation;
    double speed;
    int z_index;
    std::function<bool(BackgroundElement&, double)> mode;

    struct Mode {

        static bool stay(BackgroundElement& element, double dt);
        static bool across(BackgroundElement& element, double dt);
        static bool loop(BackgroundElement& element, double dt);

    };
};

class BackgroundMan {

public:

    using mode_func = std::function<bool(BackgroundElement&, double)>;

    static uint32_t create_element(sptr<Texture> sprite,
                                   Rectangle source,
                                   Rectangle projection,
                                   Game::Position initial_pos,
                                   double speed,
                                   double rotation,
                                   int z_index,
                                   mode_func mode);
    static void clear_background();
    static void remove_element(uint32_t id);
    static void update(double dt);
    static void draw();
    static void init();

private:

    struct ElementContainer {

        uint32_t id;
        BackgroundElement element;

    };

    inline static std::vector<ElementContainer> element_bank;
};

}
