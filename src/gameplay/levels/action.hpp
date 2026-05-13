#pragma once

namespace Engine {

class Systems;

}

namespace Game {


class Action {
public:
    virtual bool execute(Engine::Systems& sys, double dt) = 0;
    virtual void restart() = 0;

    virtual ~Action() = default;
};

};

