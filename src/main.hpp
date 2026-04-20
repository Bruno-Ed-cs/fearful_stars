#include "gameplay/ui/ui_man.hpp"
#include "systems.hpp"

Engine::Systems* setup();
bool is_running(Engine::Systems& sys);
void main_loop(Engine::Systems& sys);

extern "C" {

Engine::Systems* wrap_setup();
bool wrap_is_running(Engine::Systems& sys);
void wrap_main_loop(Engine::Systems& sys);
}
