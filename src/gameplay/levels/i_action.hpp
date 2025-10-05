#pragma once

namespace Engine {

class Systems;

class IAction {
public:
    virtual bool execute(Systems* sys, double dt) = 0;
    virtual void reset() = 0;

    virtual ~IAction() = default;
};

};

