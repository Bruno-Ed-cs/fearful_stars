#include "globals.hpp"

namespace Engine {

    Vector2 g_world_size;
    bool g_debug = false;
    bool g_running = true;

    int save_slot = 1;
    std::string level_path = "demo/demo.json";

    bool in_world_bounds(Vector2 pos) {
        if (pos.y > g_world_size.y || pos.y < 0) {
            return false;
        }

        if (pos.x > g_world_size.x || pos.x < 0) {
            return false;
        }

        return true;
    }
    bool in_world_bounds(Vector2 pos, int padding) {

        if (pos.y > g_world_size.y + padding || pos.y < 0 - padding) {
            return false;
        }

        if (pos.x > g_world_size.x + padding || pos.x < 0 - padding) {
            return false;
        }

        return true;

    }
}


