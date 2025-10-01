#include "deps.hpp"

#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "i_action.hpp"
#include "input_man.hpp"
#include "level_actions/spawn_enemies_action.hpp"
#include "level_actions/wait_action.hpp"
#include "levels.hpp"
#include "loops.hpp"
#include "control_schema.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "systems.hpp"
#include <memory>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Engine::g_window = std::make_unique<Engine::WinMan>(1280, 720, "Fearful Stars");


    Engine::g_canva_size = Vector2{320, 180};
    Engine::g_canva = LoadRenderTexture(Engine::g_canva_size.x, Engine::g_canva_size.y);


    double dt;

    Game::Assets::ship_tilemap = LoadTexture("assets/sprites/Space_pack/Space_VH.png");

    Engine::InputMan::load_events(controls);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    Engine::Systems systems{};

    systems.player.create_player1(Vector2{ 60, 150 });

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

    auto event1 = new Engine::LevelEvent("timed enemies");

    event1->add_action(new Engine::WaitAction(10));

    event1->add_action(new Engine::SpawnEnemiesAction({
        std::tuple("Basic", Vector2{22, 55}),
        std::tuple("Basic", Vector2{11, 55}),
        std::tuple("Basic", Vector2{44, 20}),
        std::tuple("Basic", Vector2{35, 20}),
        std::tuple("Basic", Vector2{98, 58}),
        std::tuple("Basic", Vector2{100, 3})
    }));

    event1->add_action(new Engine::WaitAction(5));

    event1->add_action(new Engine::SpawnEnemiesAction(
        {
            std::tuple("Basic", Vector2{300, 0}),
            std::tuple("Basic", Vector2{300, 100})
        }

    ));


    systems.level.add_event(event1);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        Engine::InputMan::pull_events();

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) 
            Engine::g_window->toggle_fullscreen();

        if (IsKeyPressed(KEY_F3)) {

            Engine::g_debug = !Engine::g_debug;

        }

        Engine::update_loop(dt, systems.enemy, systems.projectile, systems.player);

        systems.level.update(dt);

        Engine::draw_loop(systems.enemy, systems.projectile, systems.player);

        //----------------------------------------------------------------------------------
        // window.update_window();

        Engine::InputMan::flush_events();
    }

    rlImGuiShutdown();
    //Engine::InputMan::close();

    return 0;
}
