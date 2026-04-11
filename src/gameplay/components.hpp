#pragma once

#ifndef COMPONENTS_HEADER
#define COMPONENTS_HEADER 

#include "deps.hpp"
#include "container.hpp"
#include "component.hpp"

namespace Game {

    class Position : public Engine::Component {

        public:
            float x;
            float y;

        public:

            Position() :
                x(0), y(0) {};

            Position(float x, float y) :
                x(x), y(y) {};

            Position(Vector2 pos) :
                x(pos.x), y(pos.y) {};

            Vector2 vec() { return Vector2{x, y}; };

            void operator=(Vector2 pos) {
                x = pos.x;
                y = pos.y;
            };

            void operator+=(Vector2 pos) {

                x += pos.x;
                y += pos.y;

            }

    };

}

namespace Containers {

    inline static Engine::Container<Game::Position> position;

}


namespace Game {

class Direction : public Engine::Component {

public:
    float x;
    float y;

public:

    Direction() :
    x(0), y(0) {}

    Direction (float x, float y) :
    x(x), y(y) {};

    Direction(Vector2 pos) :
    x(pos.x), y(pos.y) {};

    Vector2 vec() { return Vector2Normalize(Vector2{x, y}); };

    void operator=(Vector2 pos) {

        pos = Vector2Normalize(pos);

        x = pos.x;
        y = pos.y;
    };

};

}

namespace Containers {

    inline static Engine::Container<Game::Direction> direction;

}

namespace Game {

class Hitbox : public Engine::Component {

public:

    float width;
    float height;


public:

    Hitbox(float width, float height) :
        width(width), height(height) {};

    Rectangle get(Vector2 position) {

        return Rectangle{position.x - (width / 2), position.y - (height / 2), width, height};

    };

    Rectangle get(Position position) {

        return Rectangle{position.x - (width / 2), position.y - (height / 2), width, height};

    };

};

}

namespace Containers {

    inline static Engine::Container<Game::Hitbox> hitbox;

}

namespace Game {

class Health : public Engine::Component {

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

}

namespace Containers {

    inline static Engine::Container<Game::Health> health;

}

#endif
