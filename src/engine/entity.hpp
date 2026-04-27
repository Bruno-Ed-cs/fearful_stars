#pragma once

#include "component.hpp"
#include "container.hpp"
#include "gameplay/components.hpp"
#include <stdexcept>

namespace Engine {

    struct Systems;

class Entity {

public:

    size_t self_index = 0;
    Game::ComponentMan& comp;

    Entity(Game::ComponentMan& comp) :
        comp(comp){}

    virtual ~Entity() = default;

    virtual void update(double dt, Systems& sys) = 0;
    virtual void draw(Engine::Systems& sys) = 0;
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

    using containers_ref = std::vector<ContainerHandler*>&;
    void remove(size_t index, containers_ref tracker) {

        data[index] = nullptr;
        Engine::container_cleanup_by_owner(index, tracker);

    }

    // if nullptr is returned the item was not found or is inactive
    Entity& operator[](size_t index) {

        if (data[index] == nullptr) throw std::range_error("Entity not found");

        return *data[index];

    }

};

}

