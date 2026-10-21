#pragma once

#include "deps.hpp"
#include "entity.hpp"
#include "gameplay/components/position.hpp"
#include "systems.hpp"

namespace Engine {

template<typename T>
using sptr = std::shared_ptr<T>;

struct BackgroundElement {
    
    Game::Position canva_location;
    std::string sprite_name;
    sptr<Texture> sprite;
    Rectangle source;
    Rectangle projection;
    double rotation;
    double speed;
    int z_index;
    std::function<bool(BackgroundElement&, double)> mode;

    enum struct Fn{
        stay = 1,
        across,
        loop
    } mode_id;

    struct Mode {


        static bool stay(BackgroundElement& element, double dt);
        static bool across(BackgroundElement& element, double dt);
        static bool loop(BackgroundElement& element, double dt);

    };

    Engine::Package package() {
        Engine::Package pack;

        pack["sprite_name"] = sprite_name;
        pack["canva_location_x"] = std::to_string(canva_location.x);
        pack["canva_location_y"] = std::to_string(canva_location.y);
        pack["rotation"] = std::to_string(rotation);
        pack["speed"] = std::to_string(speed);
        pack["z_index"] = std::to_string(z_index);
        pack["mode"] = std::to_string((int)mode_id);
        pack["source_width"] = std::to_string(source.width);
        pack["source_height"] = std::to_string(source.height);
        pack["source_x"] = std::to_string(source.x);
        pack["source_y"] = std::to_string(source.y);
        pack["projection_width"] = std::to_string(projection.width);
        pack["projection_height"] = std::to_string(projection.height);
        pack["projection_x"] = std::to_string(projection.x);
        pack["projection_y"] = std::to_string(projection.y);

        return pack;
    }

};

class BackgroundMan {

public:

    using mode_func = std::function<bool(BackgroundElement&, double)>;

    static uint32_t make_element(const std::string& sprite_name,
                                   Rectangle source,
                                   Rectangle projection,
                                   Game::Position initial_pos,
                                   double speed,
                                   double rotation,
                                   int z_index,
                                   BackgroundElement::Fn mode);
    static void clear_background();
    static void remove_element(uint32_t id);
    static void update(double dt);
    static void draw();
    static void init();
    static void save_background(Engine::GameState& sys);
    static void load_background(Engine::GameState& sys);

private:

    struct ElementContainer {

        uint32_t id;
        BackgroundElement element;

    };

    inline static std::vector<ElementContainer> element_bank;
};

}
