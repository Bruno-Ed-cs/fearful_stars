#pragma once 

#include "deps.hpp"
#include "input_man.hpp"

namespace Game {

struct Button {

    static bool basic(Rectangle bounds, size_t selected, size_t self_index, const std::string& content) {

        assert(self_index != 0 && "0 means no button selected");

        int text_height = 5;
        int text_wid = MeasureText(content.c_str(), text_height);
        Color highlight = (selected == self_index) ? BLUE : GRAY;
        
        DrawRectangleRec(bounds, BLACK);
        DrawRectangleLinesEx(bounds, 1, highlight);

        DrawText(content.c_str(),
                (bounds.width - text_wid) * 0.5 + bounds.x ,
                (bounds.height - text_height) * 0.3 + bounds.y,
                text_height,
                highlight);

        if (selected == self_index) {

            if (Engine::InputMan::is_event_active("ui_accept"))
                return true;
        }
        
        return false;
    }

};

}
