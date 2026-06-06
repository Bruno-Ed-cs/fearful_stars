#pragma once 

#include "deps.hpp"

namespace Game {

struct Button {

    static bool basic(Rectangle bounds, size_t selected, size_t self_index, const std::string& content) {
        
        Rectangle inner = bounds;
        inner.width -= 2;
        inner.x += 1;        
        inner.y += 1;        
        inner.height -= 2;

        int text_height = 5;
        int text_wid = MeasureText(content.c_str(), text_height);
        
        DrawRectangleRec(bounds, GRAY);
        DrawRectangleRec(inner, BLACK);

        DrawText(content.c_str(),
                (bounds.width - text_wid) * 0.5 + bounds.x ,
                (bounds.height - text_height) * 0.3 + bounds.y,
                text_height,
                WHITE);

        return false;
    }

};

}
