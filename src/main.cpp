#include "asset_man.hpp"
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
#include "raylib.h"
#include "render_man.hpp"
#include "update_loop.hpp"
#include "draw_loop.hpp"
#include "control_schema.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "systems.hpp"
#include "winman.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    
//    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, false);

    Engine::g_canva_size = Vector2{320, 180};
    Engine::g_canva = LoadRenderTexture(Engine::g_canva_size.x, Engine::g_canva_size.y);


    //load controller mappings from sdl database
    char* mappings = LoadFileText("./assets/mappings/mapping.txt");
    SetGamepadMappings(mappings);


    double dt;

    InitAudioDevice();
    Engine::AssetMan::init();
    Engine::MusicMan::init();
    Engine::RenderMan::init(320, 180);

    Engine::AssetMan::get_texture("Connor_fodder2");


    Engine::InputMan::load_events(controls);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    Engine::Systems sys{};

    sys.player->create_player1(Vector2{ 60, 150 });

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
        std::tuple("Basic", Vector2{22, 55}),
        std::tuple("Basic", Vector2{11, 55}),
        std::tuple("Basic", Vector2{44, 20}),
        std::tuple("Basic", Vector2{35, 20}),
        std::tuple("Basic", Vector2{98, 58}),
        std::tuple("Basic", Vector2{100, 3})
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

    SeekMusicStream(*Engine::AssetMan::get_music("space-ambient"), 122.0);

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
        draw_loop(sys);

        //----------------------------------------------------------------------------------
        // window.update_window();

        Engine::AssetMan::cleanup();
        Engine::InputMan::flush_events();
    }

    rlImGuiShutdown();
    return 0;
}
