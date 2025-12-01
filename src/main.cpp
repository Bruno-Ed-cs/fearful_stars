#include "asset_man.hpp"
#include "background_man.hpp"
#include "deps.hpp"

#include "gameplay/levels/level_actions/play_ost.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "gameplay/levels/i_action.hpp"
#include "input_man.hpp"
#include "gameplay/levels/level_actions/spawn_enemies_action.hpp"
#include "gameplay/levels/level_actions/wait_action.hpp"
#include "gameplay/levels/level_actions/wave_end_action.hpp"
#include "gameplay/levels/levels.hpp"
#include "music_man.hpp"
#include "render_man.hpp"
#include "ui.hpp"
#include "update_loop.hpp"
#include "draw_loop.hpp"
#include "control_schema.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "systems.hpp"
#include "winman.hpp"

void make_background() {

    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{112, 112, 16, 16}, Rectangle{0, 0, 100, 100}, Game::Position(Vector2{10, 10}), 0, 0, -1, Engine::BackgroundElement::Mode::stay);

    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{300, 10}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{201, 40}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{22, 160}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{160, 85}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

}

void make_level(Engine::Systems& sys) {

    sys.player->init_player(Vector2{ 60, 150 });

    //    auto enemy = std::make_unique<Game::BasicEnemy>();
    //    systems.enemy.insert_enemy(std::move(enemy));
    //
    //    systems.enemy.emplace_enemy("Basic", Vector2{32, 44});
    //
    //    systems.enemy.emplace_enemy("Basic", Vector2{32, 44});
    //
    //    systems.enemy.emplace_enemy("Basic", Vector2{20, 44});
    //
    //    systems.enemy.emplace_enemy("Basic", Vector2{150, 100});
    //
    //    systems.enemy.emplace_enemy("Basic", Vector2{100, 44});


    auto event1 = new Game::LevelEvent("timed enemies");

    event1->add_action(new Game::PlayOstAction("space-ambient"));

    event1->add_action(new Game::WaitAction(2));

    event1->add_action(new Game::SpawnEnemiesAction({
        std::tuple("Basic", Vector2{230, 55}),
        std::tuple("BrokenShip", Vector2{100, 100}),
        std::tuple("Basic", Vector2{222, 55}),
        std::tuple("Basic", Vector2{310, 20}),
        std::tuple("Basic", Vector2{190, 20}),
        std::tuple("Basic", Vector2{198, 58}),
        std::tuple("Basic", Vector2{200, 3})
    }));

    event1->add_action(new Game::WaitAction(1));

    event1->add_action(new Game::SpawnEnemiesAction(
        {
            std::tuple("Basic", Vector2{300, 0}),
            std::tuple("Basic", Vector2{300, 100})
        }

    ));

    event1->add_action(new Game::WaveEndAction());

    auto level = Game::Level::make_level("testes");

    event1->add_action(new Game::WaveEndAction());

    level->add_event(event1);

    sys.level->level = std::move(level);


}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, false);

    Engine::g_world_size = Vector2{320, 180};

    //load controller mappings from sdl database
    char* mappings = LoadFileText("./assets/mappings/mapping.txt");
    SetGamepadMappings(mappings);


    double dt;

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

    Engine::Systems sys{};

    SeekMusicStream(*Engine::AssetMan::get_music("space-ambient"), 122.0);

    make_level(sys);
    make_background();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        Engine::InputMan::pull_events();

        if (IsKeyPressed(KEY_ENTER)) 
            Engine::WinMan::toggle_fullscreen();

        if (IsKeyPressed(KEY_F3)) {

            Engine::g_debug = !Engine::g_debug;

        }
        Engine::WinMan::update_window();


        Engine::MusicMan::update();

        update_loop(dt, sys);

        player_ui(sys);
        draw_loop(sys);


        //----------------------------------------------------------------------------------
        // window.update_window();

        Engine::InputMan::flush_events();
    }

    rlImGuiShutdown();
    return 0;
}


