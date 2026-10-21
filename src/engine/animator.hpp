#pragma once 

#include "deps.hpp"

using string = std::string;
using string_view = std::string_view;
using path = std::filesystem::path;
using json = nlohmann::json;

namespace Engine {

struct AnimationInfo {
    size_t size;
    size_t index;
    string name;
};

struct Animator {

    bool pause = false;
    size_t animation_index = 0;
    size_t frame_index = 0;
    size_t fps;

    enum struct Transition {
        Instant = 0,
        Complete,
        Reverse,
    } transition_mode = Transition::Instant;

    double frametime = 0;
    Rectangle source_frame;


    std::vector<AnimationInfo> animations;

    Animator() = default;
    Animator(Vector2 frame_size, size_t fps, std::initializer_list<AnimationInfo> animations);
    Animator(json& animation_json);
    Animator(std::string_view animation_name);

    void update(double dt);
    void set_animation(string_view animation_name);
    bool animation_end();
    Rectangle get_frame();
};

}
