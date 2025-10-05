#pragma once

namespace Engine {

class Systems;

}

namespace Game {


class IAction {
public:
    virtual bool execute(Engine::Systems* sys, double dt) = 0;
    virtual void reset() = 0;

    virtual ~IAction() = default;
};

};

