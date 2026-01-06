#pragma once 

#include "deps.hpp"
#include "timer.hpp"

namespace Engine {

struct Animator {

    enum struct Mode {

        pause,
        loop,
        run,
        reverse_loop,
        reverse_run,
        //transition,

    };

//    enum struct Transition {
//
//        instant_begin,
//        instant_end,
//        wait_end,
//        wait_begin,
//
//    };
//
    struct Duration {

        size_t index;
        size_t length;

    };


    Rectangle frame;

    double frametime;
    double time_acumulator;
    std::unordered_map<std::string, Duration> animation_map;

    std::string cur_animation;
    std::string target_animation;

    size_t cur_frame = 0;

    Mode cur_mode = Mode::loop;
//    Transition cur_transition = Transition::instant_begin;

    using animation_def = std::tuple<std::string, Duration>;

    Animator(Vector2 frame_dimentions, std::vector<animation_def> animations, double frametime):
        frame(0, 0, frame_dimentions.x, frame_dimentions.y), time_acumulator(0), frametime(frametime) {

        for (animation_def& animation: animations) {

            animation_map[std::get<0>(animation)] = std::get<1>(animation);
        }
    }

    Rectangle get_frame() {

        return Rectangle{
            cur_frame * frame.width,
            animation_map[cur_animation].index * frame.height,
            frame.width,
            frame.height };
    }


    bool is_animation_done() {

        if (cur_frame == animation_map[cur_animation].length)
            return true;
        else 
            return false;

    }

    bool is_animation_in_begin() {

        if (cur_frame == 0)
            return true;
        else 
            return false;

    }

    void transition_animation(std::string_view animation_label) {

        if (animation_map.contains(std::string(animation_label))) {

            target_animation = animation_label;

            switch (cur_mode) {

                case Mode::pause:

                    break;

                case Mode::loop:

                    cur_frame = 0;

                    break;

                case Mode::run:

                    cur_frame = 0;

                    break;

                case Mode::reverse_loop:

                    cur_frame = animation_map[cur_animation].length;

                    break;

                case Mode::reverse_run:
                    cur_frame = animation_map[cur_animation].length;

                    break;



            }

        } else {

            throw std::logic_error(std::format("There is no animation with the label {} in this instance", animation_label));
        }
    }

    void update(double dt) {

        switch (cur_mode) {

            case Mode::pause:

                dt = 0;
                step(dt);

                break;

            case Mode::loop:

                step(dt);

                if (is_animation_done())
                    cur_frame = 0;

                break;

            case Mode::run:

                step(dt);

                break;

            case Mode::reverse_loop:

                step_reverse(dt);

                if (is_animation_in_begin())
                    cur_frame = animation_map[cur_animation].length;

                break;

            case Mode::reverse_run:

                step_reverse(dt);

                break;

//            case Mode::transition:
//
//                transition(dt);
//
//                break;
        }

    }

//    void transition(double dt) {
//
//        switch (cur_transition) {
//
//            case Transition::instant_begin:
//
//                break;
//
//            case Transition::instant_end:
//
//                break;
//
//            case Transition::wait_end:
//
//                break;
//
//            case Transition::wait_begin:
//
//                break;
//
//
//        }
//
//    }

    void step(double dt) {

        time_acumulator += dt;

        if (time_acumulator >= frametime) {


            if (cur_frame < animation_map[cur_animation].length) {

                time_acumulator = 0;
                cur_frame++;
            }

        }

    }

    void step_reverse(double dt) {

        time_acumulator += dt;

        if (time_acumulator >= frametime) {


            if (cur_frame > 0) {

                time_acumulator = 0;
                cur_frame--;
            }

        }

    }

    void reset() {


            switch (cur_mode) {

                case Mode::pause:
                    cur_frame = 0;

                    break;

                case Mode::loop:

                    cur_frame = 0;

                    break;

                case Mode::run:

                    cur_frame = 0;

                    break;

                case Mode::reverse_loop:

                    cur_frame = animation_map[cur_animation].length;

                    break;

                case Mode::reverse_run:
                    cur_frame = animation_map[cur_animation].length;

                    break;



            }


    }

};

}
