#include "deps.hpp"
#include "asset_man.hpp"
#include "globals.hpp"
#include "gameplay/levels/action.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "winman.hpp"
#include "render_man.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "gameplay/ui/interfaces/pause_ui.hpp"
#include "gameplay/levels/levels.hpp"
#include "background_man.hpp"
#include "saving.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/enemy/enemy.hpp"

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;

void gameplay_draw_loop(Engine::GameState& sys) {

    BeginDrawing();
    {

        ClearBackground(BLACK);

        if (Engine::g_debug) {

            sys.projectile->debug_world();
            sys.enemy->debug_world();
            sys.player->debug_world();
        }

        Engine::RenderMan::draw_to_window();

        if (Engine::g_debug) {

        rlImGuiBegin();

        //ImGui::ShowDemoWindow();

        ImGui::SetNextWindowPos({0, 0});
        ImGui::Begin("FPS Monitor", NULL, ImGuiWindowFlags_NoResize);
        {

            ImGui::Text("FPS: %d", GetFPS());
            ImGui::Text("Frametime %f ms", GetFrameTime());

        }
        ImGui::End();

        sys.projectile->debug_ui();
        sys.enemy->debug_ui();
        sys.player->debug_ui();

        rlImGuiEnd();
        }

    }        



    EndDrawing();

    sys.player->draw();
    sys.projectile->draw();
    sys.enemy->draw();
    sys.ui->draw();
    Engine::BackgroundMan::draw();

    Engine::RenderMan::render_to_canva();
}

void gameplay_update_loop(double dt, Engine::GameState& sys) {

    if (Engine::InputMan::is_event_active("pause") && !sys.pause) {

        sys.ui->stack_interface(std::make_unique<Game::PauseUi>(*sys.ui));
        Engine::InputMan::flush_events();
        //std::println("game paused");
    }

    if (!sys.pause) {
        sys.projectile->update(dt, sys);
        sys.enemy->update(dt, sys);
        sys.player->update(dt, sys);
        sys.level->update(sys, dt);
        Engine::BackgroundMan::update(dt);
    }

    sys.ui->update(dt, &sys);


}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void gameplay_loop(size_t save_slot, string level_path) {

    Engine::GameState sys {1};
    sys.load(level_path);

    std::string saved_level;
    rocksdb::Status status;
    status = sys.save_connection->Get(rocksdb::ReadOptions(), "Level:file", &saved_level);
    if (!status.IsNotFound()) {

        sys.load_state();

    } else {

        std::cerr << status.ToString() << std::endl;
    } 

    double dt = 0;

    // Main game loop
    while (Engine::g_running && Engine::app_state == Engine::AppState::gameplay)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        Engine::InputMan::pull_events();


        if (Engine::g_debug) {
            if (IsKeyPressed(KEY_Y)) {
                sys.save_state();
            }

            if (IsKeyPressed(KEY_U)) {
                sys.load_state();
            }
        }


        if (IsKeyPressed(KEY_I)) {

            Engine::AssetMan::cleanup();
            std::println("Cleaning assets");

        }

        Engine::WinMan::update_window();

        Engine::MusicMan::update();

        gameplay_update_loop(dt, sys);
        gameplay_draw_loop(sys);

        Engine::InputMan::flush_events();
    }

    //player_ui(sys);


    //----------------------------------------------------------------------------------
    // window.update_window();

    sys.save_state();
}


