#pragma once
#include "deps.hpp"

namespace Engine {

template <typename UserData>
struct StateMachine {

    std::array<std::function<int(StateMachine&, UserData&)>, 21> states;
    int cur_state;

    void run(UserData& data, size_t max_iterations) {

        for (int i = 0; i < max_iterations && cur_state != 0; i++) {

            cur_state = states[cur_state](*this, data);

        }
    }
};

}
