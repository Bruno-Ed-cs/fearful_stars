#include "asset_man.hpp"
#include "background_man.hpp"
#include "deps.hpp"

#include "gameplay/levels/level_actions/play_ost.hpp"
#include "gameplay/levels/level_actions/player_move_action.hpp"
#include "gameplay/levels/level_actions/spawn_upgrade_action.hpp"
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
#include "ui.hpp"
#include "update_loop.hpp"
#include "draw_loop.hpp"
#include "control_schema.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "systems.hpp"
#include "winman.hpp"
#include <print>
#include <utility>

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;

void make_background() {

    // Distribute 15 background elements across 320x180 screen
    // Group 1: Column 3 sprites (3 elements)
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{50, 30}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
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

void make_level(Engine::Systems& sys) {

    sys.player->init_player(Vector2{ 60, 90 });

    auto level = new Game::Level("level1", {
        // Wave 1
        new Game::PlayOstAction("space-ambient"),
        new Game::PlayerMoveAction(),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 10}),
            std::tuple("Basic", Vector2{360, 80}),
        }),
        new Game::WaitAction(10.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 90}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 40}),
            std::tuple("Basic", Vector2{360, 150}),
            std::tuple("Basic", Vector2{360, 100}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),

        // Wave 2
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 35}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 110}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 90}),
        }),
        new Game::WaitAction(2.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 160}),
        }),
        new Game::WaitAction(2.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{360, 40}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),

        // Wave 3
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 55}),
        }),
        new Game::WaitAction(3.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 20}),
            std::tuple("BrokenShip", Vector2{360, 140}),
        }),
        new Game::WaitAction(2.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 100}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 180}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),

        // Wave 4
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 20}),
            std::tuple("BrokenShip", Vector2{360, 150}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnEnemiesAction({
            std::tuple("CrystalEye", Vector2{360, 50}),
        }),
        new Game::WaitAction(4.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("CrystalEye", Vector2{360, 150}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),

        // Wave 5
        new Game::SpawnEnemiesAction({
            std::tuple("CrystalEye", Vector2{360, 20}),
            std::tuple("CrystalEye", Vector2{360, 150}),
        }),
        new Game::WaitAction(4.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("CrystalEye", Vector2{360, 90}),
            std::tuple("CrystalEye", Vector2{360, 177}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),
        new Game::WaitAction(3.0f),

        // Wave 6
        new Game::SpawnEnemiesAction({
            std::tuple("Anemonae", Vector2{360, 90}),
        }),
        new Game::WaitAction(3.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("CrystalEye", Vector2{360, 20}),
            std::tuple("CrystalEye", Vector2{360, 177}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnEnemiesAction({
            std::tuple("Anemonae", Vector2{360, 30}),
            std::tuple("Anemonae", Vector2{360, 130}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("CrystalEye", Vector2{360, 30}),
            std::tuple("CrystalEye", Vector2{360, 130}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),
        new Game::WaitAction(3.0f),

        // Wave 7
        new Game::SpawnEnemiesAction({
            std::tuple("Anemonae", Vector2{360, 70}),
        }),
        new Game::WaitAction(3.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Anemonae", Vector2{360, 140}),
        }),
        new Game::WaitAction(2.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Vagant", Vector2{360, 40}),
            std::tuple("Vagant", Vector2{360, 170}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Anemonae", Vector2{360, 80}),
            std::tuple("Anemonae", Vector2{360, 130}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),
        new Game::WaitAction(3.0f),

        // Wave 8
        new Game::SpawnEnemiesAction({
            std::tuple("Chaser", Vector2{360, 70}),
        }),
        new Game::WaitAction(3.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Chaser", Vector2{360, 140}),
        }),
        new Game::WaitAction(7.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Vagant", Vector2{360, 90}),
            std::tuple("Chaser", Vector2{360, 60}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Chaser", Vector2{360, 80}),
            std::tuple("Chaser", Vector2{360, 20}),
            std::tuple("Chaser", Vector2{360, 130}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),
        new Game::WaitAction(3.0f),

        // Wave 9
        new Game::SpawnEnemiesAction({
            std::tuple("Vagant", Vector2{360, 40}),
            std::tuple("Vagant", Vector2{360, 150}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Minion", Vector2{360, 80}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Minion", Vector2{360, 80}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),
        new Game::WaitAction(3.0f),

        // Wave 10
        new Game::SpawnEnemiesAction({
            std::tuple("BrokenShip", Vector2{360, 90}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnEnemiesAction({
            std::tuple("Chaser", Vector2{360, 80}),
            std::tuple("Chaser", Vector2{360, 170}),
            std::tuple("Minion", Vector2{360, 90}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Anemonae", Vector2{360, 40}),
            std::tuple("Anemonae", Vector2{360, 160}),
        }),
        new Game::WaitAction(5.0f),
        new Game::SpawnEnemiesAction({
            std::tuple("Minion", Vector2{360, 80}),
            std::tuple("Minion", Vector2{360, 10}),
            std::tuple("Vagant", Vector2{360, 130}),
        }),
        new Game::WaveEndAction(),
        new Game::SpawnUpgradeAction(),
        new Game::WaitAction(5.0f),
    }, {                                  
                                 {"anemonae", AssRef::sprite},
                                 {"basic_proj", AssRef::sprite},
                                 {"broken_ship", AssRef::sprite},    
                                 {"chaser", AssRef::sprite},         
                                 {"Connor_fodder2", AssRef::sprite}, 
                                 {"cursor", AssRef::sprite},         
                                 {"eye", AssRef::sprite},            
                                 {"meteorite", AssRef::sprite},      
                                 {"minion", AssRef::sprite},         
                                 {"missile", AssRef::sprite},        
                                 {"orbital_proj", AssRef::sprite},   
                                 {"plasma_proj", AssRef::sprite},    
                                 {"player", AssRef::sprite},         
                                 {"player_ui", AssRef::sprite},      
                                 {"super_proj", AssRef::sprite},
                                 {"upgrade_proj", AssRef::sprite},
                                 {"vagant", AssRef::sprite},           
                                 {"vic_viper", AssRef::sprite}         
                                 });                                   


    auto teste = new Game::Level("testes", {
        new Game::WaitAction(2),
        new Game::SpawnUpgradeAction(),
        new Game::SpawnEnemiesAction({
            std::tuple("Basic", Vector2{230, 55}),
            std::tuple("Anemonae", Vector2{200, 120}),
            std::tuple("Vagant", Vector2{300, 120}),
            std::tuple("Anemonae", Vector2{300, 100}),
            std::tuple("Anemonae", Vector2{300, 20}),
            std::tuple("Chaser", Vector2{320, 190}),
            std::tuple("Chaser", Vector2{320, 10}),
            std::tuple("Chaser", Vector2{320, 100}),
            std::tuple("CrystalEye", Vector2{ 190, 110}),
            std::tuple("CrystalEye", Vector2{ 107, 101}),
            std::tuple("CrystalEye", Vector2{ 101, 200}),
            std::tuple("BrokenShip", Vector2{100, 100}),
            std::tuple("Basic", Vector2{222, 55}),
            std::tuple("Minion", Vector2{10, 10}),
            std::tuple("Basic", Vector2{310, 20}),
            std::tuple("Basic", Vector2{190, 20}),
            std::tuple("Basic", Vector2{198, 58}),
            std::tuple("Basic", Vector2{200, 3})
        }),
        new Game::WaitAction(1),
        new Game::SpawnEnemiesAction(
            {
                std::tuple("Basic", Vector2{300, 0}),
                std::tuple("Basic", Vector2{300, 100})
            }

        ),
        new Game::WaveEndAction(),

    }, 
                                 {
                                 {"anemonae", AssRef::sprite},
                                 {"basic_proj", AssRef::sprite},
                                 {"broken_ship", AssRef::sprite},
                                 {"chaser", AssRef::sprite},
                                 {"Connor_fodder2", AssRef::sprite},
                                 {"cursor", AssRef::sprite},
                                 {"eye", AssRef::sprite},
                                 {"meteorite", AssRef::sprite},
                                 {"minion", AssRef::sprite},
                                 {"missile", AssRef::sprite},
                                 {"orbital_proj", AssRef::sprite},
                                 {"plasma_proj", AssRef::sprite},
                                 {"player", AssRef::sprite},
                                 {"player_ui", AssRef::sprite},
                                 {"super_proj", AssRef::sprite},
                                 {"upgrade_proj", AssRef::sprite},
                                 {"vagant", AssRef::sprite},
                                 {"vic_viper", AssRef::sprite}
                                 });


    //auto level = Game::Level::make_level("level1");

    //level->add_event(wave1);
    //level->add_event(wave2);
    //level->add_event(wave3);
    //level->add_event(wave4);
    //level->add_event(wave5);
    //level->add_event(wave6);
    //level->add_event(wave7);
    //level->add_event(wave8);
    //level->add_event(wave9);
    //level->add_event(wave10);

    std::unique_ptr<Game::Level> level_ptr(level);
    sys.level->level = std::move(level_ptr);

}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    srand(time(NULL));

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, true);

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

    //make_level(sys);
    sys.level->load_level("demo/demo.json");
    sys.player->init_player({90, 60});
    make_background();

    // Main game loop
    while (Engine::g_running)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        Engine::InputMan::pull_events();

        if (WindowShouldClose()) 
            Engine::g_running = false;

        if (IsKeyPressed(KEY_ENTER)) 
            Engine::WinMan::toggle_fullscreen();

        if (IsKeyPressed(KEY_F3)) {

            Engine::g_debug = !Engine::g_debug;

        }

        
        if (IsKeyPressed(KEY_I)) {

            Engine::AssetMan::cleanup();
            std::println("Cleaning assets");

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

    return 0;
}


