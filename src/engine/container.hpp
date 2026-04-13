#pragma once 

#include "component.hpp"
#include "deps.hpp"
#include <optional>
#include <stdexcept>

#define INIT_SIZE 255


// when putting something here in a container it servers as a public api, the components still can be used as normal variables

template <typename T>
concept component = std::is_base_of_v<Engine::Component, T>;

namespace Engine {

    struct ContainerHandler {
        
        virtual void cleanup() = 0;
        virtual void remove(size_t index) = 0;
        virtual void remove_by_owner(size_t owner) = 0;


    };
}



namespace Containers {

    inline std::vector<Engine::ContainerHandler*> containers;

    inline void cleanup_by_owner(size_t owner) {

        for(auto& container : containers) {

            container->remove_by_owner(owner);
        }


    };
}

namespace Engine {


    template<component comp>
    struct Container: public ContainerHandler {

        std::vector<comp> data;

        Container() {

            data.reserve(INIT_SIZE);
            Containers::containers.push_back(this);

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

        void remove(size_t index) override {

            if (data[index].active) data[index].active = false;
            //std::cout << "Removed: " << index << "\n";

        }

        void remove_by_owner(size_t owner) override {

            for (size_t i = 0; i < data.size(); ++i) {

                if (*this->data[i].entity_owner == owner) {

                    remove(i);
                }

            }

        }

        void cleanup() override {

            data.clear();
            data.reserve(INIT_SIZE);

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

        std::vector<size_t> querry_by_owner(size_t owner) {

            std::vector<size_t> result;

            for (size_t i = 0; i < data.size(); i++) {

                if (*data[i].entity_owner == owner) {

                    result.push_back(i);
                }

            }

            return result;

        }

        std::optional<size_t> querry_by_owner_first(size_t owner) {


            for (size_t i = 0; i < data.size(); i++) {

                if (*data[i].entity_owner == owner) {

                    return owner;
                }

            }

            return std::nullopt;


        }

        std::optional<size_t> first() {

            if (!data.empty()) return 0;
            return std::nullopt;
        }
    };


}


