#pragma once

#include "deps.hpp"
#include "component.hpp"


namespace Game {

class Health : public Engine::IComponent {

public:

    int points;
    int capacity;

    Health(int max_hp) :
        points(max_hp),
        capacity(max_hp) {};

    std::string get_name() override { return "Health"; };

    void take_damage(int damage) {

        points -= damage;

        if (points < 0)
            points = 0;

    };

    bool is_dead() {

        if (points <= 0)
            return true;

        return false;

    };

    void restore() {

        points = capacity;

    };



};

}
