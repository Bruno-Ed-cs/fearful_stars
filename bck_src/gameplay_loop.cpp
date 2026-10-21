#include "deps.hpp"
#include "asset_man.hpp"
#include "globals.hpp"
#include "gameplay/levels/action.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "timer.hpp"
#include "winman.hpp"
#include "render_man.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "gameplay/ui/interfaces/pause_ui.hpp"
#include "gameplay/levels/levels.hpp"
#include "background_man.hpp"
#include "saving.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/projectile/basic/basic_projectile.hpp"
#include "gameplay/enemy/enemy.hpp"
#include <chrono>
#include <future>

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;
using namespace std::chrono_literals;

constexpr int stress_iterations = 100'000;

void debug_entry(Engine::GameState& sys) {

    static bool measuring = false;
    static double acumulator = 0;
    static double frames = 0;
    static Engine::Timer duration;

    ImGui::Begin("Benchmarks");

    ImGui::Text("Projectile Stress test");

    if (ImGui::Button("Test") && measuring == false) {
        measuring = true;

        for (int i = 0; i <= stress_iterations; i++) {
            sys.projectile->emplace<Game::BasicProjectile>({10, 10}, {1, 0}, 10, true);
        }
        duration.set_limit(5.0);
        duration.reset();
    }

    ImGui::End();

    if (measuring) {

        double dt = GetFrameTime();

        frames++;
        acumulator += dt;
        duration.update(dt);

        if (duration.past_limit()) {
        
            std::println("Projectile strees results:\nAvarege frametime: {}\nAvarege fps: {}", acumulator/frames, 1.0 / (acumulator/frames));
            measuring = false;
            acumulator = 0;
            frames = 0;


        }

    }

}

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
        debug_entry(sys);

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
        // std::println("game paused");
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

    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Loading...", 0, 0, 70, WHITE);
    EndDrawing();

    Engine::GameState sys {save_slot};
    sys.load(level_path);

    std::string saved_level;
    rocksdb::Status status;
    status = sys.save_connection->Get(rocksdb::ReadOptions(), "Level:file", &saved_level);
    if (!status.IsNotFound()) {

        auto start {std::chrono::high_resolution_clock().now()};

        sys.load_state();

        // std::atomic<bool> loaded {false};
        // std::thread loader {[&]() {
        //     sys.load_state();
        //     loaded = true;
        //
        // }};
        //
        // while (!loaded) {
        //     std::println("waiting....");
        // }
        //
        // loader.join();

        auto end {std::chrono::high_resolution_clock().now()};

        std::println("{} to load", std::chrono::duration<double> {end - start});
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
            // std::println("Cleaning assets");

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


