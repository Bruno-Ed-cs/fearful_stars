#pragma once

#include "deps.hpp"

namespace Engine {

//The names must perfect match the name of the derived class
class IComponent {

public:

    virtual std::string get_name() = 0;

    virtual ~IComponent() = default;

};

template<typename T>
concept is_component = std::is_base_of_v<IComponent, T>;

class ComponentContainer {


public:

    ComponentContainer() :
    m_components() {};



    ComponentContainer(std::initializer_list<IComponent*> components) :
    m_components() {

        for (auto& component : components) {

            m_components.emplace(component->get_name(), std::move(component));
            
        };

    }

    ComponentContainer(std::span<IComponent*> components) :
    m_components() {

        for (auto& component : components) {

            m_components.emplace(component->get_name(), std::move(component));
            
        };

    }

    template<is_component Component>
    bool has_component() noexcept{

        return m_components.contains(typeid(Component).name());

    }
    template<is_component Component>
    void remove_component() {

        auto ref = m_components.find(typeid(Component).name());

        if (ref == m_components.end()) 
            throw std::logic_error(std::format("Component {} not found", typeid(Component).name()));
        
        m_components.erase(ref);

    }

    void add_component(IComponent&& component) {

        m_components.emplace(component.get_name(), &component);

    }

    template<is_component Component>
    Component& get() {

        auto ref = m_components.find(typeid(Component).name());

        if (ref == m_components.end()) 
            throw std::logic_error(std::format("Component {} not found", typeid(Component).name()));

        return dynamic_cast<Component&>(*ref->second);

    };

private:

    std::map<std::string, std::unique_ptr<IComponent>> m_components; 

};

}
