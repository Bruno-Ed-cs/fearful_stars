#include "asset_man.hpp"
#include "background_man.hpp"
#include "deps.hpp"

#include "entity.hpp"
#include "gameplay/components.hpp"
#include "gameplay/ui/interfaces/gameplay_ui.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "gameplay/levels/i_action.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "update_loop.hpp"
#include "draw_loop.hpp"
#include "control_schema.hpp"
#include "systems.hpp"
#include "winman.hpp"
#include <cstdio>
#include <print>

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;

void make_background() {
    // Distribute 15 background elements across 320x180 screen
    // Group 1: Column 3 sprites (3 elements)
    Engine::BackgroundMan::create_element(
            Engine::AssetMan::get_texture("earthBackgroudeErased"),
            Rectangle{16 * 3, 0, 16, 16},
            Rectangle{0, 0, 16, 16},
            Game::Position(Vector2{50, 30}),
            0, 0, 0,
            Engine::BackgroundElement::Mode::stay);

    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{270, 150}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{160, 90}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    // Group 2: Column 2 sprites (4 elements)  
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{240, 40}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{80, 140}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{300, 100}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{20, 50}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    // Group 3: Column 1 sprites (4 elements)
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{100, 20}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{220, 160}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{40, 100}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{280, 60}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    // Group 4: Column 0 sprites (4 elements)
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{140, 120}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{60, 160}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{200, 30}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{300, 170}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

}


Engine::Systems* setup() {

    srand(time(NULL));

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------


    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, true);

    //load controller mappings from sdl database
    char* mappings = LoadFileText("./assets/mappings/mapping.txt");
    SetGamepadMappings(mappings);
    UnloadFileText(mappings);



    InitAudioDevice();
    Engine::AssetMan::init();
    Engine::MusicMan::init();
    Engine::RenderMan::init(320, 180);
    Engine::BackgroundMan::init();

    Engine::AssetMan::get_texture("Connor_fodder2");


    Engine::InputMan::load_events(controls);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    auto sys = new Engine::Systems();

    sys->entity.insert(std::make_unique<Game::Player>(*sys));

    //make_level(sys);
    //sys.level->load_level("demo/demo.json");
    //sys.player->init_player({90, 60});
    sys->ui->stack_interface(std::make_unique<Game::GameplayUi>());
    make_background();

    return sys;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void main_loop(Engine::Systems& sys)
{
    // Main game loop
    //std::cout << "check 3";
    //dou
    double dt = GetFrameTime();
    Engine::InputMan::pull_events();
    

    if (WindowShouldClose()) 
        sys.running = false;

    if (IsKeyPressed(KEY_ENTER)) 
        Engine::WinMan::toggle_fullscreen();

    if (IsKeyPressed(KEY_F3)) {

        sys.debug = !sys.debug;

    }


    if (IsKeyPressed(KEY_I)) {
        Engine::AssetMan::cleanup();
        std::println("Cleaning assets");
    }

    Engine::WinMan::update_window();

    Engine::MusicMan::update();

    update_loop(dt, sys);

    //player_ui(sys);
    draw_loop(sys);


    //----------------------------------------------------------------------------------
    // window.update_window();

    Engine::InputMan::flush_events();

    // std::cout << Containers::hitbox.data.size() << std::endl << std::endl;
    //
    // std::printf("say something");
    // for (auto& hitbox : Containers::hitbox.data) {
    //
    //     std::cout << hitbox.self_index << ", owner: " << *hitbox.entity_owner << std::endl;
    //
    // }

}

bool is_running(Engine::Systems& sys) {

    return sys.running;
}

extern "C" {

Engine::Systems* wrap_setup() { return setup(); };
bool wrap_is_running(Engine::Systems& sys) { return is_running(sys); };
void wrap_main_loop(Engine::Systems& sys) { return main_loop(sys);}
}
