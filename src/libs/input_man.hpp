#pragma once

#include "deps.hpp"

namespace engine {

struct Event {

    std::string name;
    std::vector<KeyboardKey> keyboard_inputs;
    std::vector<GamepadButton> gamepad_inputs;
};

class InputMan {
public:

    static void pull_events(); // call at the beggining of the game loop;
    static void flush_events(); // call at the end of the game loop;

    static bool is_event_active(const std::string& event_name);
    static void load_events(const std::vector<Event>& events);
    static void add_input_to_event(const std::string& event_name, const int new_input);

    static void close();

    constexpr static size_t buffer_size = 10;

private:

    static InputMan* instance;

    std::vector<Event> m_event_pool;
    
    struct Buffer {

        std::array<size_t, buffer_size> active_buffer;
        size_t buffer_end = 0;

    } m_input_buffer;

    void activate_event(const std::string& event_name);

    size_t get_event_index(const std::string& event_name);

    void flush_active_buffer();

    InputMan() {

        m_event_pool = std::vector<Event>();
    };

    static InputMan& get_instance() {

        if (instance == nullptr) 
            instance = new InputMan();

        return *instance;
    }

};

}
