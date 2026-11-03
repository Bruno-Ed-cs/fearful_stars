#include <array>
#include <cstdio>


typedef int32_t idx;

namespace Engine {
    template <typename T, size_t n> 
    struct RecycleArray{

        idx limit = 0;
        std::array<bool, n> m_meta {};
        std::array<T, n> m_data {};

        T& operator[](idx index) {

            return m_data[index];
        }

        const size_t size() {
            return n;
        }

        bool is_active(idx index) {

            return m_meta[index];
        }

        idx activate(T item) {

            for (int i = 1; i < m_meta.size(); i++) {
                if (!m_meta[i]) {
                    m_meta[i] = true;
                    m_data[i] = item;

                    if (i >= limit) {
                        limit = i + 1;
                    }
                    return i;
                }
            }

            return 0;

        }

        void deactivate(idx index) {

            m_meta[index] = false;
            if (index >= limit) {
                for (int i = index; i > 0; i--) {
                    if (m_meta[i]) {
                        limit = i + 1;
                        break;
                    }
                    if (i <= 1) {
                        limit = 0;
                    }

                }

            }

        }

        idx begin() {
            return 1;
        }

        idx end() {
            return limit;

        }

    };

}
