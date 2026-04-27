#include "main.hpp"
#include "raylib.h"
#include <dlfcn.h>

using loop_func = void (*)(Engine::Systems&);
using setup_func = Engine::Systems* (*)();
using is_key_pressed_func = bool (*)(int);

void* gamelib = NULL;
loop_func main_loop = NULL;
setup_func setup = NULL;
is_key_pressed_func is_key_pressed = NULL;

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

    main_loop = (loop_func)dlsym(gamelib, "wrap_main_loop");
    setup = (setup_func)dlsym(gamelib, "wrap_setup");
    is_key_pressed = (is_key_pressed_func)dlsym(gamelib, "IsKeyPressed");

    if (!is_key_pressed) {

        fprintf(stderr, "Error loading IsKeyPressed: %s\n", dlerror());
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

    auto sys = setup();

    while(sys->running) {

        main_loop(*sys);

        if (is_key_pressed(KEY_R)) {

            std::println("reloading.....");
            if (!load_game()) {

                fprintf(stderr, "Error loading game: %s\n", dlerror());
                return 1;
            }
        }

    }

    std::cout << "this is on the dev runner" << std::endl;

}
