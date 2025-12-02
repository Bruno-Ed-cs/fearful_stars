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


    //auto event1 = new Game::LevelEvent("timed enemies");
    auto wave1 = new Game::LevelEvent("wave1");
    auto wave2 = new Game::LevelEvent("wave2");
    auto wave3 = new Game::LevelEvent("wave3");
    auto wave4 = new Game::LevelEvent("wave4");
    auto wave5 = new Game::LevelEvent("wave5");
    auto wave6 = new Game::LevelEvent("wave6");
    auto wave7 = new Game::LevelEvent("wave7");
    auto wave8 = new Game::LevelEvent("wave8");
    auto wave9 = new Game::LevelEvent("wave9");
    auto wave10 = new Game::LevelEvent("wave10");

    wave1->add_action(new Game::PlayOstAction("space-ambient"));

    wave1->add_action(new Game::PlayerMoveAction());

    wave1->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 10}),
        std::tuple("Basic", Vector2{360 , 80}),

    }));

    wave1->add_action(new Game::WaitAction(10.0f));
    wave1->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 90}),

    }));

    wave1->add_action(new Game::WaitAction(5.0f));
    wave1->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 40}),
        std::tuple("Basic", Vector2{360, 150}),
        std::tuple("Basic", Vector2{360, 100}),

    }));

    wave1->add_action(new Game::WaveEndAction());

    wave1->add_action(new Game::SpawnUpgradeAction());

    wave1->add_action(new Game::WaveEndAction());




    wave2->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 35}),

    }));

    wave2->add_action(new Game::WaitAction(5.0f));
    wave2->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 110}),

    }));

    wave2->add_action(new Game::WaitAction(5.0f));
    wave2->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 90}),

    }));

    wave2->add_action(new Game::WaitAction(2.0f));
    wave2->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 160}),

    }));

    wave2->add_action(new Game::WaitAction(2.0f));
    wave2->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Basic", Vector2{360, 40}),

    }));

    wave2->add_action(new Game::WaveEndAction());

    wave2->add_action(new Game::SpawnUpgradeAction());


    wave3->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 55}),

    }));


    wave3->add_action(new Game::WaitAction(3.0f));
    wave3->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 20}),
        std::tuple("BrokenShip", Vector2{360, 140}),

    }));


    wave3->add_action(new Game::WaitAction(2.0f));
    wave3->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 100}),

    }));

    wave3->add_action(new Game::WaveEndAction());
    wave3->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 180}),

    }));

    wave3->add_action(new Game::WaveEndAction());

    wave3->add_action(new Game::SpawnUpgradeAction());

    wave3->add_action(new Game::WaveEndAction());


    wave4->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 20}),
        std::tuple("BrokenShip", Vector2{360, 150}),

    }));

    wave4->add_action(new Game::WaveEndAction());
    wave4->add_action(new Game::SpawnEnemiesAction({

        std::tuple("CrystalEye", Vector2{360, 50}),

    }));

    wave4->add_action(new Game::WaitAction(4.0f));
    wave4->add_action(new Game::SpawnEnemiesAction({

        std::tuple("CrystalEye", Vector2{360, 150}),

    }));

    wave4->add_action(new Game::WaveEndAction());

    wave4->add_action(new Game::SpawnUpgradeAction());

    wave4->add_action(new Game::WaveEndAction());


    wave5->add_action(new Game::SpawnEnemiesAction({

        std::tuple("CrystalEye", Vector2{360, 20}),
        std::tuple("CrystalEye", Vector2{360, 150}),

    }));

    wave5->add_action(new Game::WaitAction(4.0f));
    wave5->add_action(new Game::SpawnEnemiesAction({


        std::tuple("CrystalEye", Vector2{360, 90}),
        std::tuple("CrystalEye", Vector2{360, 177}),

    }));

    wave5->add_action(new Game::WaveEndAction());

    wave5->add_action(new Game::SpawnUpgradeAction());

    wave5->add_action(new Game::WaitAction(3.0f));


    wave6->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Anemonae", Vector2{360, 90}),

    }));

    wave6->add_action(new Game::WaitAction(3.0f));
    wave6->add_action(new Game::SpawnEnemiesAction({


        std::tuple("CrystalEye", Vector2{360, 20}),
        std::tuple("CrystalEye", Vector2{360, 177}),

    }));

    wave6->add_action(new Game::WaveEndAction());
    wave6->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Anemonae", Vector2{360, 30}),
        std::tuple("Anemonae", Vector2{360, 130}),

    }));

    wave6->add_action(new Game::WaitAction(5.0f));
    wave6->add_action(new Game::SpawnEnemiesAction({


        std::tuple("CrystalEye", Vector2{360, 30}),
        std::tuple("CrystalEye", Vector2{360, 130}),

    }));


    wave6->add_action(new Game::WaveEndAction());

    wave6->add_action(new Game::SpawnUpgradeAction());

    wave6->add_action(new Game::WaitAction(3.0f));


    wave7->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Anemonae", Vector2{360, 70}),

    }));

    wave7->add_action(new Game::WaitAction(3.0f));
    wave7->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Anemonae", Vector2{360, 140}),

    }));

    wave7->add_action(new Game::WaitAction(2.0f));
    wave7->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Vagant", Vector2{360, 40}),
        std::tuple("Vagant", Vector2{360, 170}),

    }));

    wave7->add_action(new Game::WaitAction(5.0f));
    wave7->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Anemonae", Vector2{360, 80}),
        std::tuple("Anemonae", Vector2{360, 130}),

    }));


    wave7->add_action(new Game::WaveEndAction());

    wave7->add_action(new Game::SpawnUpgradeAction());

    wave7->add_action(new Game::WaitAction(3.0f));


    wave8->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Chaser", Vector2{360, 70}),

    }));

    wave8->add_action(new Game::WaitAction(3.0f));
    wave8->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Chaser", Vector2{360, 140}),

    }));

    wave8->add_action(new Game::WaitAction(7.0f));
    wave8->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Vagant", Vector2{360, 90}),
        std::tuple("Chaser", Vector2{360, 60}),

    }));

    wave8->add_action(new Game::WaitAction(5.0f));
    wave8->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Chaser", Vector2{360, 80}),
        std::tuple("Chaser", Vector2{360, 20}),
        std::tuple("Chaser", Vector2{360, 130}),

    }));


    wave8->add_action(new Game::WaveEndAction());

    wave8->add_action(new Game::SpawnUpgradeAction());

    wave8->add_action(new Game::WaitAction(3.0f));


    wave9->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Vagant", Vector2{360, 40}),
        std::tuple("Vagant", Vector2{360, 150}),

    }));

    wave9->add_action(new Game::WaitAction(5.0f));
    wave9->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Minion", Vector2{360, 80}),

    }));

    wave9->add_action(new Game::WaitAction(5.0f));
    wave9->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Minion", Vector2{360, 80}),

    }));

    wave9->add_action(new Game::WaveEndAction());

    wave9->add_action(new Game::SpawnUpgradeAction());

    wave9->add_action(new Game::WaitAction(3.0f));


    wave10->add_action(new Game::SpawnEnemiesAction({

        std::tuple("BrokenShip", Vector2{360, 90}),

    }));

    wave10->add_action(new Game::WaveEndAction());
    wave10->add_action(new Game::SpawnEnemiesAction({


        std::tuple("Chaser", Vector2{360, 80}),
        std::tuple("Chaser", Vector2{360, 170}),
        std::tuple("Minion", Vector2{360, 90}),

    }));

    wave10->add_action(new Game::WaitAction(5.0f));
    wave10->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Anemonae", Vector2{360, 40}),
        std::tuple("Anemonae", Vector2{360, 160}),

    }));

    wave10->add_action(new Game::WaitAction(5.0f));
    wave10->add_action(new Game::SpawnEnemiesAction({

        std::tuple("Minion", Vector2{360, 80}),
        std::tuple("Minion", Vector2{360, 10}),
        std::tuple("Vagant", Vector2{360, 130}),

    }));

    wave10->add_action(new Game::WaveEndAction());

    wave10->add_action(new Game::SpawnUpgradeAction());

    wave10->add_action(new Game::WaitAction(5.0f));
    wave10->add_action(new Game::WaitAction(5.0f));




                      //
                      //    
                      //
                      //    event1->add_action(new Game::WaitAction(2));
                      //
                      //    event1->add_action(new Game::SpawnUpgradeAction());
                      //
                      //    event1->add_action(new Game::SpawnEnemiesAction({
                      //        std::tuple("Basic", Vector2{230, 55}),
                      //        std::tuple("Anemonae", Vector2{200, 120}),
                      //        std::tuple("Vagant", Vector2{300, 120}),
                      //        std::tuple("Anemonae", Vector2{300, 100}),
                      //        std::tuple("Anemonae", Vector2{300, 20}),
                      //        std::tuple("Chaser", Vector2{320, 190}),
                      //        std::tuple("Chaser", Vector2{320, 10}),
                      //        std::tuple("Chaser", Vector2{320, 100}),
                      //        std::tuple("CrystalEye", Vector2{ 190, 110}),
                      //        std::tuple("CrystalEye", Vector2{ 107, 101}),
                      //        std::tuple("CrystalEye", Vector2{ 101, 200}),
                      //        std::tuple("BrokenShip", Vector2{100, 100}),
                      //        std::tuple("Basic", Vector2{222, 55}),
                      //        std::tuple("Minion", Vector2{10, 10}),
                      //        std::tuple("Basic", Vector2{310, 20}),
                      //        std::tuple("Basic", Vector2{190, 20}),
                      //        std::tuple("Basic", Vector2{198, 58}),
                      //        std::tuple("Basic", Vector2{200, 3})
                      //    }));
                      //
                      //    event1->add_action(new Game::WaitAction(1));
                      //
                      //    event1->add_action(new Game::SpawnEnemiesAction(
                      //        {
                      //            std::tuple("Basic", Vector2{300, 0}),
                      //            std::tuple("Basic", Vector2{300, 100})
                      //        }
                      //
                      //    ));
                      //
                      //    event1->add_action(new Game::WaveEndAction());
                      //
                      //    auto level = Game::Level::make_level("testes");
                      //
                      //    event1->add_action(new Game::WaveEndAction());
                      //
                      //    level->add_event(event1);


                      

    auto level = Game::Level::make_level("level1");

    level->add_event(wave1);
    level->add_event(wave2);
    level->add_event(wave3);
    level->add_event(wave4);
    level->add_event(wave5);
    level->add_event(wave6);
    level->add_event(wave7);
    level->add_event(wave8);
    level->add_event(wave9);
    level->add_event(wave10);

    sys.level->level = std::move(level);

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

    make_level(sys);
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


