#include "globals.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "systems.hpp"
#include "raylib.h"
#include <dlfcn.h>

using loop_func = void (*)(Engine::Systems&);
using setup_func = Engine::Systems (*)();

void* gamelib = NULL;
loop_func main_loop = NULL;
setup_func setup = NULL;

bool load_game() {

    if (gamelib != NULL) dlclose(gamelib);

    gamelib = dlopen("libgame.so", RTLD_NOW); 
    if (gamelib == NULL) {

        fprintf(stderr, "Error loading game: %s\n", dlerror());
        return false;
    }

    main_loop = (loop_func)dlsym(gamelib, "main_loop");
    setup = (setup_func)dlsym(gamelib, "setup");

    if (!main_loop) {

        fprintf(stderr, "Error loading main loop: %s\n", dlerror());
        return false;

    }

    if (!setup) {

        fprintf(stderr, "Error loading setup: %s\n", dlerror());
        return false;
    }

    printf("Loading Game.....\n");
    return true;

}

int main() {


    if (!load_game()) {

        fprintf(stderr, "Error loading game: %s\n", dlerror());
        return 1;

    }

    Engine::Systems sys = setup();

    while(Engine::g_running) {

        main_loop(sys);

        if (IsKeyPressed(KEY_R)) {

            if (!load_game()) {

                fprintf(stderr, "Error loading game: %s\n", dlerror());
                return 1;
            }
        }

    }

}
