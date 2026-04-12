#pragma once

#include "systems.hpp"
#include "container.hpp"
#include <stdexcept>

namespace Engine {

class Entity {

public:

    size_t self_index = 0;

    virtual ~Entity() = default;

    virtual void update(double dt, Systems& sys) = 0;
    virtual void draw() = 0;
    virtual bool destroy_self() = 0;

};

struct EntityContainer {

    std::vector<std::unique_ptr<Engine::Entity>> data;

    EntityContainer() {

        data.reserve(255);
    }

    size_t insert(std::unique_ptr<Entity> entity) {

        for (size_t i = 0; i < data.size(); i++) {

            if (data[i] == nullptr){

                data[i] = std::move(entity);
                data[i]->self_index = i;
                return i;
            }

        }

        data.emplace_back(std::move(entity));
        size_t i = data.size() -1; 
        data[i]->self_index = i;

        return i;

    }

    void remove(size_t index) {

        data[index] = nullptr;

    }

    // if nullptr is returned the item was not found or is inactive
    Entity& operator[](size_t index) {

        if (data[index] == nullptr) throw std::range_error("Entity not found");

        return *data[index];

    }

};

}

namespace Containers {

    inline Engine::EntityContainer entity;

}


