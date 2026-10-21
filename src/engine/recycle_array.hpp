#include <array>
#include <cstdio>


typedef int32_t idx;

namespace Engine {
    template <typename T, size_t n> 
    struct RecycleArray{

        std::array<bool, n> m_meta {};
        std::array<T, n> m_data {};

        T& operator[](idx index) {

            return m_data[index];
        }

        idx activate(T item) {

            for (int i = 1; i < m_meta.size(); i++) {
                if (!m_meta[i]) {
                    m_meta[i] = true;
                    m_data[i] = item;
                    return i;
                }
            }

            return 0;

        }

        void deactivate(idx index) {

            m_meta[index] = false;

        }

    };

}
