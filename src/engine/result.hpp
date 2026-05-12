#pragma once
#include "deps.hpp"

namespace Engine {

    template<typename T>
    struct Result {
        
        enum class Status {
            ok = 1,
            err,
            partial
        };

        Status stat = Status::ok;
        uint32_t err = 0;

        T data;
    };

}
