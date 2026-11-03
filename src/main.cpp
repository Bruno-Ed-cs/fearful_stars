#include "asset_man.hpp"
#include "deps.hpp"

#include "game/game.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "control_schema.hpp"
#include "rlImGui.h"
#include "winman.hpp"


#include "gamecontrollerdb.h"

void gameplay_loop(size_t save_slot, string level_path);
void main_menu_loop();

using string = std::string;

void debug(Game& gm) {
    rlImGuiBegin(); 

    auto& m_player1 = gm.actors[gm.player];
    ImGui::Begin("Player debug");
    {
        Vector2 position = m_player1.pos.vec();

        ImGui::Text("Position:\nx: %f\ny: %f", position.x, position.y);
        ImGui::Text("Shooting cooldown: %f", m_player1.cooldown.get_time());
        ImGui::Text("Special meter: %d", m_player1.special_meter);
        ImGui::Text("Lives: %d", m_player1.lives.points);
        ImGui::Text("Dead: %d", m_player1.dead);
        ImGui::Text("Upgrades: %d", m_player1.upgrade);
        ImGui::Text("invis_timer: %03f", m_player1.invis_timer.get_time());
        ImGui::Text("damage_intake: %d", m_player1.damage_intake);

        if (ImGui::Button("Revive")) {

            m_player1.lives.restore();

        }

        if (ImGui::Button("Fill special")) {

            m_player1.special_meter = 100;

        }



        ImGui::Text("Primary level");
        ImGui::SliderInt("Lv##1", &m_player1.primary_level, 1, 3, "%d");

        ImGui::Text("Secondary Level");
        ImGui::SliderInt("Lv##2", &m_player1.secondary_level, 0, 2, "%d");


        ImGui::Text("Aux Level");
        ImGui::SliderInt("Lv##3", &m_player1.aux_level, 0, 2, "%d");

        ImGui::Text("Upgrades");

        if (ImGui::Button("+")) {
            m_player1.upgrade++;

        }

        ImGui::SameLine();
        if (ImGui::Button("-")) {

            m_player1.upgrade--;
        }

    }
    ImGui::End();

    rlImGuiEnd();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    srand(time(NULL));
    SetTraceLogLevel(LOG_INFO);

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, false);

    Engine::g_world_size = Vector2{320, 180};

    //load controller mappings from sdl database

    int output = SetGamepadMappings((char*)GAMECONTROLLERDB_DATA);
    //std::println("mappings result: {}", output);

    std::println("game size: {}", sizeof(Game));

    Engine::AssetMan::init();
    Engine::MusicMan::init();

    Engine::AssetMan::get_texture("Connor_fodder2");

    Engine::InputMan::load_events(controls);
    rlImGuiSetup(true);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    Game* game = new Game();
    RenderTexture2D view = LoadRenderTexture(Engine::g_world_size.x, Engine::g_world_size.y);

    Engine::AssetMan::load_all();

    // Engine::AssetMan::CurrentlyLoading cur {};
    // std::thread loader {Engine::AssetMan::load_all_stepped, &cur};
    //
    // while (Engine::g_running && !loader.joinable()) {
    //     Engine::WinMan::update_window();
    //     BeginDrawing();
    //
    //     ClearBackground(BLACK);
    //
    //     switch(cur) {
    //
    //         case Engine::AssetMan::CurrentlyLoading::TEXTURES: {
    //                                                                DrawText("Loading Sprites", 0, 0, 10, WHITE);
    //                                                            } break;
    //         case Engine::AssetMan::CurrentlyLoading::MUSICS: {
    //                                                              DrawText("Loading Musics", 0, 0, 10, WHITE);
    //                                                          } break;
    //         case Engine::AssetMan::CurrentlyLoading::SOUNDS: {
    //                                                              DrawText("Loading Sounds", 0, 0, 10, WHITE);
    //                                                          } break;
    //         case Engine::AssetMan::CurrentlyLoading::FONTS: {
    //                                                             DrawText("Loading Fonts", 0, 0, 10, WHITE);
    //                                                         } break;
    //         case Engine::AssetMan::CurrentlyLoading::ANIMATIONS: {
    //                                                                  DrawText("Loading Animations", 0, 0, 10, WHITE);
    //                                                              } break;
    //         case Engine::AssetMan::CurrentlyLoading::JSON: {
    //                                                            DrawText("Loading Json", 0, 0, 10, WHITE);
    //                                                        } break;
    //         case Engine::AssetMan::CurrentlyLoading::SHADERS: {
    //                                                              DrawText("Loading Shaders", 0, 0, 10, WHITE);
    //                                                          } break;
    //
    //     }
    //
    //     EndDrawing();
    // }
    //
    // loader.join();

    // Main game loop
    while (Engine::g_running)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";

        Engine::WinMan::update_window();
        Engine::InputMan::pull_events();

        game->update();

        BeginDrawing();

        ClearBackground(BLACK);

        BeginTextureMode(view);

        ClearBackground(BLACK);
        game->draw();

        EndTextureMode();

        Rectangle dest = {0, 0, (float)Engine::WinMan::get_width(), (float)Engine::WinMan::get_height()};
        DrawTexturePro(view.texture, {0, 0, Engine::g_world_size.x, -Engine::g_world_size.y}, dest, {0, 0}, 0.0, WHITE);

        if (Engine::g_debug) {
            debug(*game);
        }

        DrawFPS(0, 0);

        EndDrawing();
        Engine::InputMan::flush_events();
    }

    UnloadRenderTexture(view);
    rlImGuiShutdown();
    return 0;
}


