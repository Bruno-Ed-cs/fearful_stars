#pragma once

#include "input_man.hpp"
#include "raylib.h"
#include <vector>

static Engine::Event controls[] = {

    {
        "pause",
        std::vector{KEY_P},
        std::vector{GAMEPAD_BUTTON_MIDDLE_RIGHT},
        Engine::Event::Trigger::pressed

    },

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

    {
        "ui_up",
        std::vector{KEY_UP},
        std::vector{GAMEPAD_BUTTON_LEFT_FACE_UP},
        Engine::Event::Trigger::released
    },
    {
        "ui_down",
        std::vector{KEY_DOWN},
        std::vector{GAMEPAD_BUTTON_LEFT_FACE_DOWN},
        Engine::Event::Trigger::released
    },
    {
        "ui_left",
        std::vector{KEY_LEFT},
        std::vector{GAMEPAD_BUTTON_LEFT_FACE_LEFT},
        Engine::Event::Trigger::released
    },
    {
        "ui_right",
        std::vector{KEY_RIGHT},
        std::vector{GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
        Engine::Event::Trigger::released
    },
    {
        "ui_accept",
        std::vector{KEY_Z},
        std::vector{GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
        Engine::Event::Trigger::released
    },
    {
        "ui_deny",
        std::vector{KEY_X},
        std::vector{GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
        Engine::Event::Trigger::released

    },

};
