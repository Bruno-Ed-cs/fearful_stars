#pragma once 

#include "component.hpp"
#include <stdexcept>

template <typename T>
concept component = std::is_base_of_v<Engine::Component, T>;

namespace Engine {
        template<component comp>
        struct Container {

            std::vector<comp> data;

            Container() {

                data.reserve(255);
            }

            size_t insert(comp component, size_t* owner) {

                for (size_t i = 0; i < data.size(); i++) {

                    if (!data[i].active){

                        data[i] = component;
                        data[i].entity_owner = owner;
                        data[i].self_index = i;
                        return i;
                    }

                }

                data.push_back(component);
                size_t i = data.size() -1; 
                data[i].entity_owner = owner;
                data[i].self_index = i;

                return i;

            }

            void remove(size_t index) {

                if (data[index].active) data[index].active = false;
            }

            // if nullptr is returned the item was not found or is inactive
            comp* get_ptr(size_t index) {

                if (index >= data.size()) return nullptr;

                if (!data[index].active) return nullptr;

                return &data[index];

            }

            //can throw an error if the item is not in the array
            comp& operator[](size_t index) {

                if (index > data.size()) throw std::range_error("component not found");

                if (!data[index].active) std::range_error("component not found");

                return data[index];

            }

            comp get_copy(size_t index) {

                if (index >= data.size()) throw std::range_error("component not found");

                if (!data[index].active) std::range_error("component not found");

                return data[index];

            }
        };


}

