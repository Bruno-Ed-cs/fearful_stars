#include "background_man.hpp"
#include "deps.hpp"
#include "globals.hpp"
#include "music_man.hpp"
#include "render_man.hpp"
#include "systems.hpp"
#include "input_man.hpp"
#include "winman.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "gameplay/ui/interfaces/main_menu_ui.hpp"

void main_menu_loop() {

    Game::UiMan ui_manager = Game::UiMan(Engine::RenderMan::canva_size());

    ui_manager.stack_interface(std::make_unique<Game::MainMenuUi>(ui_manager));

    while(Engine::g_running && Engine::app_state == Engine::AppState::main_menu) {

        double dt = GetFrameTime();

        Engine::InputMan::pull_events();
        Engine::WinMan::update_window();
        Engine::MusicMan::update();
        Engine::BackgroundMan::update(dt);
        ui_manager.update(dt);

        BeginDrawing(); {

            ClearBackground(BLACK);

            Engine::RenderMan::render_to_canva();
            Engine::RenderMan::draw_to_window();
            ui_manager.draw();
        } EndDrawing();

        Engine::InputMan::flush_events();

    }

}
