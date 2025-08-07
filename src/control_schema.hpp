#pragma once

#include "deps.hpp"
#include "input_man.hpp"

static engine::Event controls[] = {

    {
    "shoot",
    std::vector{KEY_SPACE, KEY_C},
    std::vector{GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, GAMEPAD_BUTTON_RIGHT_FACE_LEFT}
    },

    {
    "move_up",
    std::vector{KEY_UP, KEY_W},
    std::vector{GAMEPAD_BUTTON_LEFT_FACE_UP}
    },

    {
    "move_down",
    std::vector{KEY_DOWN, KEY_S},
    std::vector{GAMEPAD_BUTTON_LEFT_FACE_DOWN}
    },

    {
    "move_left",
    std::vector{KEY_LEFT, KEY_A},
    std::vector{GAMEPAD_BUTTON_LEFT_FACE_LEFT}
    },

    {
    "move_right",
    std::vector{KEY_RIGHT, KEY_D},
    std::vector{GAMEPAD_BUTTON_LEFT_FACE_RIGHT}
    },

};
