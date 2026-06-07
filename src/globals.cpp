#include "globals.hpp"

namespace Engine {

    Vector2 g_world_size;
    bool g_debug = false;
    bool g_running = true;

    AppState app_state = Engine::AppState::main_menu;
    int save_slot = 1;
    std::string level_path = "demo/demo.json";
}


