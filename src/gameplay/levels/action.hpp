#pragma once

namespace Engine {

class GameState;

}

namespace Game {

    enum struct ActionType {
        Action,
        PlayOstAction,

    };

class Action {
public:
    virtual bool execute(Engine::GameState& sys, double dt) = 0;
    virtual void restart() = 0;

    virtual ActionType type() { return ActionType::Action; };

    virtual ~Action() = default;
};

};

