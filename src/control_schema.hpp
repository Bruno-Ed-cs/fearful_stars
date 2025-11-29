#pragma once

#include "input_man.hpp"
#include "raylib.h"

static Engine::Event controls[] = {
    {

        "upgrade",
        std::vector{KEY_Z, KEY_I},
        std::vector{GAMEPAD_BUTTON_RIGHT_FACE_RIGHT}

    },

    {
        "special",
        std::vector{KEY_LEFT_CONTROL, KEY_RIGHT_CONTROL},
        std::vector{GAMEPAD_BUTTON_RIGHT_FACE_UP}


    },

    {
        "slowdown",
        std::vector{KEY_RIGHT_SHIFT, KEY_LEFT_SHIFT},
        std::vector{GAMEPAD_BUTTON_LEFT_TRIGGER_1}
    },

    {
        "shoot",
        std::vector{KEY_SPACE, KEY_C},
        std::vector{GAMEPAD_BUTTON_RIGHT_FACE_LEFT}
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
