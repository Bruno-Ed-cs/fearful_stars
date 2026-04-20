#include "globals.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "systems.hpp"
#include "raylib.h"
#include <dlfcn.h>

using loop_func = void (*)(Engine::Systems&);
using setup_func = Engine::Systems (*)();
using running_func = bool (*)();

void* gamelib = NULL;
loop_func main_loop = NULL;
setup_func setup = NULL;
running_func running = NULL;

bool load_game() {

    if (gamelib != NULL) {
        dlclose(gamelib);
        gamelib = NULL;
    }

    gamelib = dlopen("./libgame.so", RTLD_NOW); 
    if (gamelib == NULL) {

        fprintf(stderr, "Error loading game: %s\n", dlerror());
        return false;
    }

    main_loop = (loop_func)dlsym(gamelib, "main_loop");
    setup = (setup_func)dlsym(gamelib, "setup");
    running = (running_func)dlsym(gamelib, "is_running");

    if (!running) {

        fprintf(stderr, "Error loading g_running: %s\n", dlerror());
        return false;
    }

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

    while(running()) {

        main_loop(sys);

        if (IsKeyPressed(KEY_R)) {

            if (!load_game()) {

                fprintf(stderr, "Error loading game: %s\n", dlerror());
                return 1;
            }
        }

    }

}
