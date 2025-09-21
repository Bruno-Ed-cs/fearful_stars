#pragma once

#include "deps.hpp"

namespace Engine {

//The names must perfect match the name of the derived class
class IComponent {

public:

    virtual std::string get_name() = 0;

    virtual ~IComponent() = default;

};

class ComponentContainer {

public:

    ComponentContainer() :
    m_components() {};

    ComponentContainer(std::span<IComponent*> components) :
    m_components() {

        for (auto& component : components) {

            m_components.emplace(component->get_name(), component);
            
        };

    }

    bool has_component(const std::string& component_name) noexcept{

        return m_components.contains(component_name);

    }

    IComponent& operator[](const std::string& component_name) {

        auto ref = m_components.find(component_name);

        if (ref == m_components.end()) 
            throw std::logic_error(std::format("Component {} not found", component_name));

        return *ref->second;

    }

    void remove_component(const std::string& component_name) {

        auto ref = m_components.find(component_name);

        if (ref == m_components.end()) 
            throw std::logic_error(std::format("Component {} not found", component_name));
        
        m_components.erase(ref);

    }

    void add_component(IComponent&& component) {

        m_components.emplace(component.get_name(), &component);

    }

private:

    std::map<std::string, std::unique_ptr<IComponent>> m_components; 

};

}
