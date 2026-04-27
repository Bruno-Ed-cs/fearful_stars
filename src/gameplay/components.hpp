#pragma once


#include "deps.hpp"
#include "container.hpp"
#include "component.hpp"
#include "timer.hpp"
#include <vector>

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




struct PlayerTag : public Engine::Component {
};




struct EnemyTag : public Engine::Component {
};




struct ProjectileTag : public Engine::Component {

    bool is_foe = true;

};



struct Timer : Engine::Timer, Engine::Component  {


    Timer(): Engine::Timer() {}

    Timer(double seconds) :
        Engine::Timer(seconds) {}


};



struct ComponentMan: Engine::ComponentHeader {

    Engine::Container<Timer>              timer {tracker};
    Engine::Container<Hitbox>             hitbox {tracker};
    Engine::Container<Direction>          direction {tracker};
    Engine::Container<Position>           position {tracker};
    Engine::Container<Health>             health {tracker};
    Engine::Container<PlayerTag>          player_tag {tracker};
    Engine::Container<ProjectileTag>      projectile_tag {tracker};
    Engine::Container<EnemyTag>           enemy_tag {tracker};
};

}
