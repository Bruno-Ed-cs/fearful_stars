#pragma once

#include "deps.hpp"

#include "i_entity.hpp"

namespace Game {

class SimpleProj : public Engine::IEntity{

public:

    bool is_foe();
    Rectangle get_hitbox();
    Vector2 get_position();
    double get_speed();
    const std::type_info& get_type();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe);

};

}
