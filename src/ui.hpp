#pragma once
#include "asset_man.hpp"
#include "deps.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include "gameplay/player/player_manager.hpp"
#include <format>


void player_ui(Engine::Systems& sys) {

    static std::shared_ptr<Texture2D> ui_texture = Engine::AssetMan::get_texture("player_ui");
    static std::shared_ptr<Texture2D> cursor_texture = Engine::AssetMan::get_texture("cursor");


    static auto screen_canva = LoadRenderTexture(320, 180);

    Rectangle bar = Rectangle{1, 91, 4, 0};
    //95 21 74

    int special = sys.player->get_player().special_meter;
    int lives = sys.player->get_player().lives.points;
    int upgrades = sys.player->get_player().upgrade;

    int height = 76 * (special / 100.0f);
    bar.height = height;
    bar.y = 96 - height;

    std::string live_text = std::format("x {}", lives);


    BeginTextureMode(screen_canva);
        ClearBackground(ColorAlpha(WHITE, 0.0));


        DrawRectangleRec(bar, YELLOW);
        DrawTextureEx(*ui_texture, Vector2{0,0}, 0.0f, 1.0f, WHITE);

        DrawText(live_text.c_str(), 0, 0, 1, WHITE);

        switch (upgrades) {

            case 0:
            break;

            case 1:
                DrawTextureEx(*cursor_texture, Vector2{10, 118}, 1.0f, 1.0f, WHITE);
            break;

            case 2:
                DrawTextureEx(*cursor_texture, Vector2{10, 129}, 1.0f, 1.0f, WHITE);
            break;               

            case 3:
                DrawTextureEx(*cursor_texture, Vector2{10, 140}, 1.0f, 1.0f, WHITE);
            break;

            default:
                DrawTextureEx(*cursor_texture, Vector2{10, 151}, 1.0f, 1.0f, WHITE);
            break;

        
        }
        
        

    EndTextureMode();

    Engine::RenderMan::send_texture(Engine::RenderMan::Plane::front, screen_canva.texture, Rectangle{0, 0, 320, 180}, Rectangle{0, 0, 320, -180});

}
