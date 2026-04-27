#pragma once 

namespace Engine {

class Component {

public:

    size_t* entity_owner = nullptr;
    size_t self_index = 0;
    bool active = true;

    virtual ~Component() = default;
};


}
