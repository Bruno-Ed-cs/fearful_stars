#pragma once

#include "deps.hpp"
#include "entity.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/components.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "systems.hpp"

namespace Game {

struct GameplayUi: UiLayer {

    GameplayUi() {

        ui_texture = Engine::AssetMan::get_texture("player_ui");
        cursor_texture = Engine::AssetMan::get_texture("cursor");

    }

    void update(double dt, Engine::Systems& sys) {

//
        auto player_tag = Containers::player_tag.first();

        if (!player_tag) return;

        size_t player_index = player_tag.value();
        auto& player = dynamic_cast<Player&>(Containers::entity[player_index]);

        special = player.special_meter;
        upgrades = player.upgrade;
        bar = Rectangle{1, 91, 4, 0};

        auto life_querry = Containers::health.querry_by_owner(player_index);

        if (!life_querry.empty()) {
            size_t life = life_querry.front();
            lives = Containers::health[life].points;
        }

        int height = 76 * (special / 100.0f);
        bar.height = height;
        bar.y = 96 - height;


    }

    void draw(RenderTexture canva) {


        BeginTextureMode(canva);

        DrawRectangleRec(bar, YELLOW);
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

            default:
                DrawTextureEx(*cursor_texture, Vector2{10, 151}, 1.0f, 1.0f, WHITE);
                break;


        }

        EndTextureMode();
    }

    void process_input(Engine::Systems& sys) {}

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
