#include "animator.hpp"
#include "asset_man.hpp"
#include "deps.hpp"
#include "json.hpp"
#include "raylib.h"

using namespace Engine;

Animator::Animator(Vector2 frame_size, size_t fps, std::initializer_list<AnimationInfo> animations):
    animations(animations.begin(), animations.end()),
    source_frame({.x = 0, .y = 0, .width = frame_size.x, .height = frame_size.y}),
    fps(fps) {}

Animator::Animator(std::string_view animation_name) {

    // char* file_data = LoadFileText(animation_json.c_str());
    // defer(UnloadFileText(file_data));
    //
    // json animation = json::parse(file_data);
    //
    std::shared_ptr<json> animation_json {Engine::AssetMan::get_json(animation_name)};

    fps = (*animation_json)["fps"].get<size_t>();
    source_frame = {
        .x = 0,
        .y = 0,
        .width = (*animation_json)["frame_size"]["width"].get<float>(),
        .height = (*animation_json)["frame_size"]["height"].get<float>(),
    };

    for (auto& info : (*animation_json)["animations"]) {
        animations.emplace_back(
                info["size"].get<size_t>(),
                info["index"].get<size_t>(),
                info["name"].get<string>()
        );
    }
    //completar depois

}

Animator::Animator(json& animation_json) {

    // char* file_data = LoadFileText(animation_json.c_str());
    // defer(UnloadFileText(file_data));
    //
    // json animation = json::parse(file_data);

    fps = animation_json["fps"].get<size_t>();
    source_frame = {
        .x = 0,
        .y = 0,
        .width = animation_json["frame_size"]["width"].get<float>(),
        .height = animation_json["frame_size"]["height"].get<float>(),
    };

    for (auto& info : animation_json["animations"]) {
        animations.emplace_back(
                info["size"].get<size_t>(),
                info["index"].get<size_t>(),
                info["name"].get<string>()
        );
    }
    //completar depois

}

void Animator::update(double dt) {

    if (!pause)
        frametime += dt;

    if (frametime >= 1 / (double)fps) {

        frame_index++;
        frametime = 0;
    }

    if (frame_index >= animations.at(animation_index).size) 
        frame_index = 0;

}

auto Animator::set_animation(string_view animation_name) -> void {

    auto ani_info = std::find_if(animations.begin(), animations.end(), [&](AnimationInfo info) {
        if (info.name == animation_name)
            return true;
        return false;
    });

    if (ani_info != animations.end()) {
        animation_index = ani_info->index;
    }

}

auto Animator::get_frame() -> Rectangle {

    return Rectangle {
        .x = source_frame.width * frame_index,
        .y = source_frame.height * animation_index,
        .width = source_frame.width,
        .height = source_frame.height
    };
}

auto Animator::animation_end() -> bool {

    if (frame_index == animations.at(animation_index).size -1) 
        return true;

    return false;

}
