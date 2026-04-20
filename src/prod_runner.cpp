#include "main.hpp"
#include "raylib.h"


int main() {

    auto sys = setup();

    while(is_running(*sys)) {

        main_loop(*sys);

    }

    delete sys;
    CloseWindow();

}
