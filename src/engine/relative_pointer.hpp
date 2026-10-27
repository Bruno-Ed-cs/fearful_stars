#pragma once

namespace Engine {

    template <typename T>
    struct RelativePtr {

        std::span<T> m_origin;
        std::size_t m_idx;

        RelativePtr(std::span<T> origin, std::size_t idx) {

        }

    }

}
