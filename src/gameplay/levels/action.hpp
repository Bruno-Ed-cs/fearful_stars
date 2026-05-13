#pragma once

namespace Engine {

class GameState;

}

namespace Game {


class Action {
public:
    virtual bool execute(Engine::GameState& sys, double dt) = 0;
    virtual void restart() = 0;

    virtual ~Action() = default;
};

};

