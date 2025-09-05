#pragma once 
#include <functional>

namespace Engine {

template<typename system>
uint32_t generate_id(const std::function<bool(uint32_t)> id_exists) {

    constexpr const uint32_t int_lim_32 = 4294967295;

    static uint32_t biggest_id = 0;

    if (biggest_id == int_lim_32) {

        uint32_t ran_id = rand() % int_lim_32;
        while (id_exists(ran_id)) {

            ran_id = rand() % int_lim_32;
        }

        return ran_id;

    } else {

        biggest_id++;
        return biggest_id;

    }
}


}
