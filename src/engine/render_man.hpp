#pragma once
#include "deps.hpp"

namespace Engine {

struct RenderElement {

    Texture source;
    Rectangle render_view;
    Rectangle source_view;
    int z_index = 0;
    double rotation = 0.0;
    Color tint;
//    std::optional<Shader> effect;
//    std::function<void(RenderElement*, double)> script = nullptr;
};

class RenderMan {
    
    //send sprites and location on canva
    //make background
    //make background elements move
    //have z levels
    //
    //buffer 
    //have the rendering to the window a winman thing
    //move the canva to here

public:
    enum class Plane {
        front,
        middle,
        back,
        ui
    };

    static void send_texture(RenderMan::Plane layer, Texture sprite,
                             Rectangle render_view, Rectangle source_view,
                             int z_index = 0, double rotation = 0, Color tint = WHITE);

    static void init(int canva_wid, int canva_hei);
    static void draw_to_window();

    static RenderTexture& get_canva();
    static Camera2D& get_camera();

    static void render_to_canva();

    static void begin_draw_debug();
    static void end_draw_debug();
    
    static Vector2 canva_size();

            // void setup_sprite() {
            //
            //     Image sprite = LoadImageFromTexture(*this->spritesheet);
            //     int size = sprite.height * sprite.width;
            //     Color* tar_arr = LoadImageColors(sprite);
            //     Color* col_arr = LoadImageColors(sprite);
            //
            //     for (int i = 0; i < size; i++) {
            //         int left = i +1;
            //         int right = i -1;
            //         int down = i + sprite.width;
            //         int up = i - sprite.width;
            //
            //         if (left >= size) left = size -1;
            //         if (up < 0) up = 0;
            //         if (down >= size) down = size -1;
            //         if (right < 0) right = 0;
            //
            //         if (ColorIsEqual(col_arr[i], BLANK) && !ColorIsEqual(col_arr[i], PURPLE) &&
            //                 (
            //                  !ColorIsEqual(col_arr[left],  BLANK) ||
            //                  !ColorIsEqual(col_arr[down],  BLANK) ||
            //                  !ColorIsEqual(col_arr[right], BLANK) ||
            //                  !ColorIsEqual(col_arr[up],    BLANK) 
            //                 ) ) {
            //
            //             tar_arr[i] = PURPLE;
            //         }
            //     }
            //
            //
            //     UpdateTexture(*spritesheet, tar_arr);
            //     UnloadImageColors(col_arr);
            //     UnloadImageColors(tar_arr);
            //     UnloadImage(sprite);
            //
            // }
private:

    using buffer = std::vector<RenderElement>;


    inline static bool s_initialized;

    inline static RenderTexture s_canva;
    inline static buffer s_background;
    inline static buffer s_middleground;
    inline static buffer s_foreground;
    inline static buffer s_ui;
    inline static Camera2D s_camera;

};

}
