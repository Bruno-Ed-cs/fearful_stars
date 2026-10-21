#pragma once

#include "deps.hpp"
#include "component.hpp"



class Health {

public:

    int points;
    int capacity;

    Health(int max_hp) :
        points(max_hp),
        capacity(max_hp) {};


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

