#include "gameplay/ui/ui_man.hpp"
#include "systems.hpp"

extern "C" {

Engine::Systems* wrap_setup();
bool wrap_is_running(Engine::Systems* sys);
void wrap_main_loop(Engine::Systems* sys);
}
