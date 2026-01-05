#pragma once 

#include "deps.hpp"
#include "timer.hpp"
#include <string_view>

namespace Engine {

struct Animator {

    enum struct Mode {

        loop,
        run,
        reverse_loop,
        reverse_run,

    };

    enum struct Transition {

        instant_begin,
        instant_end,
        wait_end,
        wait_begin,

    };

    Rectangle frame;
    double dt;
    double frametime;
    std::unordered_map<std::string, size_t> animation_map;
    std::string cur_animation;

    Mode cur_mode = Mode::loop;
    Transition cur_transition = Transition::instant_begin;

    Animator(Vector2 frame_dimentions, std::vector<std::string_view> animation_labels, double frametime):
    frame(0, 0, frame_dimentions.x, frame_dimentions.y), dt(0), frametime(frametime) {


    }

    void update(double dt) {

    }

    Rectangle get_frame() {

    }

    void transition_animation(std::string_view animation_label) {

    }

    bool is_animation_done() {

    }







};

}
