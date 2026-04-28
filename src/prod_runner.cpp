#include "main.hpp"
#include "raylib.h"


int main() {

    auto* sys = wrap_setup();

    while(sys->running) {

        wrap_main_loop(sys);

    }

    delete sys;
    CloseWindow();

}
