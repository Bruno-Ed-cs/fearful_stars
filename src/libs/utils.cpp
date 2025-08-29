#include "deps.hpp"
 
#include "utils.hpp"


using namespace Engine;


void vector2_round(Vector2& vec){

    vec.x = std::round(vec.x);
    vec.y = std::round(vec.y);

    return;
}
