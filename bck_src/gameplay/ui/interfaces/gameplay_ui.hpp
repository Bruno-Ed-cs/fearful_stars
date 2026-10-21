#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player.hpp"
#include "raylib.h"
#include "systems.hpp"

namespace Game {

struct GameplayUi: public UiLayer {

    UiMan& manager;

    GameplayUi(UiMan& manager):
    manager(manager){

        ui_texture = Engine::AssetMan::get_texture("player_ui");
        cursor_texture = Engine::AssetMan::get_texture("cursor");

    }

    void update(double dt, Engine::GameState* sys) {

        special = sys->player->get_player().special_meter;
        lives = sys->player->get_player().lives.points;
        upgrades = sys->player->get_player().upgrade;
        bar = Rectangle{1, 91, 4, 0};

        int height = 76 * (special / 100.0f);
        bar.height = height;
        bar.y = 96 - height;


    }

    void draw(RenderTexture canva) {


        BeginTextureMode(canva);

        if (special < 100)
            DrawRectangleRec(bar, YELLOW);
        else
            DrawRectangleRec(bar, BLUE);

        DrawTextureEx(*ui_texture, Vector2{0,0}, 0.0f, 1.0f, WHITE);


        std::string live_text = std::format("x {}", lives);
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

            case 4: 

                DrawTextureEx(*cursor_texture, Vector2{10, 151}, 1.0f, 1.0f, WHITE);
                break;

            default:
                DrawTextureEx(*cursor_texture, Vector2{10, 151}, 1.0f, 1.0f, WHITE);
                std::string extra_upgrades = std::format("+ {}", upgrades - 4);
                DrawText(extra_upgrades.c_str(), 0, 161, 1, WHITE);
                break;


        }

        EndTextureMode();
    }

    std::shared_ptr<Texture> ui_texture;
    std::shared_ptr<Texture> cursor_texture;

    Rectangle bar {1, 91, 4, 0};
    int special = 0;
    int lives = 0;
    int upgrades = 0;

};

}

//void player_ui(Engine::Systems& sys) {
//
//    static std::shared_ptr<Texture2D> 
//    static std::shared_ptr<Texture2D> 
//
//
//    static auto screen_canva = LoadRenderTexture(320, 180);
//
//    Rectangle 
//    //95 21 74
//
//
//    Engine::RenderMan::send_texture(Engine::RenderMan::Plane::front, screen_canva.texture, Rectangle{0, 0, 320, 180}, Rectangle{0, 0, 320, -180});
//
//}
