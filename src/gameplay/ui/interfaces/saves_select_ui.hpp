#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "render_man.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "gameplay/ui/elements/button.hpp"
#include <filesystem>
#include <string>

namespace Game {

struct SaveSelectUi: public UiLayer {

    RenderTexture ui;
    UiMan& manager;
    uint32_t selected = 0;
    bool delete_mode = false;

    SaveSelectUi(UiMan& manager):
    manager(manager){

        auto size = Engine::RenderMan::canva_size();
        ui = LoadRenderTexture(size.x, size.y);

    }

    ~SaveSelectUi() {

        UnloadRenderTexture(ui);
    }

    void update(double dt, Engine::GameState* sys) {

       BeginTextureMode(ui); {

           Rectangle box = {((float)ui.texture.width - 160) /2, 20, 160, 140};
           std::array<Rectangle, 3> save_buttons{0};
           for (int i = 0; i < save_buttons.size(); i++) {
               int wid = 120;
               int hei = 28;
               save_buttons[i].width = wid;
               save_buttons[i].x = box.x + (box.width - wid) /2;
               save_buttons[i].height = hei;
               save_buttons[i].y = (box.y + 18) + (hei * i) + (3 * i);
           }
           Rectangle delete_button = {box.x + (box.width - 80) / 2, box.y + box.width - 45, 80, 21};

           Color highlight = {0};
           std::string title = {0};
            if (delete_mode) {
                highlight = RED;
                title = "Delete Save";
            } else {
                highlight = BLUE;
                title = "Load Save";
            }


           DrawRectangleRec(box, BLACK);
           DrawRectangleLinesEx(box, 1, highlight);
           int title_width = MeasureText(title.c_str(), 3);
           DrawText(title.c_str(), box.x + (box.width - title_width) /2, box.y +4, 3, delete_mode ? VIOLET : WHITE);

           int num = 0;
           for (auto& button: save_buttons) {
               std::string save_text = {0};
               std::string save_dir = GetApplicationDirectory();
               save_dir += "saves/" + std::to_string(num + 1);
               //std::println("savedir : {}", save_dir);
               if (DirectoryExists(save_dir.c_str())) {
                   save_text = "Save Slot " + std::to_string(num +1);
               } else {
                    save_text = "New Game";
               }

                if (Button::basic(button, selected, num, save_text, delete_mode ? RED : BLUE)) {
                    if (delete_mode) {
                        std::filesystem::path path = save_dir;
                        std::filesystem::remove_all(path);

                    } else {

                        Engine::save_slot = num + 1;
                        Engine::app_state = Engine::AppState::gameplay;
                        return;
                    }
                }

                num++;
           }

           if (Button::basic(delete_button, selected, num, delete_mode ? "Cancel":"Delete Save")) {

               delete_mode = !delete_mode;
           }

           selected = UiMan::selector(selected, num);

       } EndTextureMode();

       if (Engine::InputMan::is_event_active("ui_deny")) {
           manager.pop_interface();
           return;

       }

    }

    void draw(RenderTexture canva) {

        Engine::RenderMan::send_texture(
                Engine::RenderMan::Plane::ui,
                ui.texture,
                Rectangle {0, 0, (float)ui.texture.width, (float)ui.texture.height},
                Rectangle {0, 0, (float)ui.texture.width, (float)ui.texture.height * -1});
        
    }


};

}

