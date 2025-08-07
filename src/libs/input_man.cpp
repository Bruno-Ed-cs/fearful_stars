#include "input_man.hpp"

using namespace engine;

InputMan* InputMan::instance = nullptr;

void InputMan::pull_events() {

    auto& instance = InputMan::get_instance();

    for (auto event : instance.m_event_pool) {

        for (auto key_input : event.keyboard_inputs) {

            if (IsKeyDown(key_input)) {

                instance.activate_event(event.name);
                break;

            }

        }

        for (auto gamepad_input : event.gamepad_inputs) {

            for (size_t i = 0; i <= 10; ++i){

                if (IsGamepadButtonDown(i, gamepad_input)) {

                    instance.activate_event(event.name);
                    break;
                }
            }
        }

    }


}// call at the beggining of the game loop;

void InputMan::flush_events() {
    auto& instance = InputMan::get_instance();

    instance.flush_active_buffer();


}// call at the end of the game loop;

bool InputMan::is_event_active(const std::string& event_name){ 

    auto& instance = InputMan::get_instance();
    bool active = false;

    size_t index = instance.get_event_index(event_name);

    for (size_t i = 0; i < instance.m_input_buffer.buffer_end; ++i) {

        if (index == instance.m_input_buffer.active_buffer[i]) {

            active = true;
            break;

        }

    }

    return active;

}

void InputMan::load_events(std::span<Event> events) {

    auto& instance = InputMan::get_instance();

    for (Event event : events) {

        instance.m_event_pool.push_back(event);

    }

}

void InputMan::add_input_to_event(const std::string& event_name, const int new_input) {

}


//void InputMan::close() {
//
//    auto instance = InputMan::get_instance();
//    delete &instance;
//
//}

size_t InputMan::get_event_index(const std::string& event_name) {

    size_t index = 0;
    bool found = false;

    for (size_t i = 0; i < m_event_pool.size(); ++i) {

        //std::cout << m_event_pool[i].name << '\n';

        if (m_event_pool[i].name == event_name){

            index = i;
            found = true;
            break;

        }

    }

    if (!found) {

        throw std::invalid_argument("Event not found in event pool");
    }

    return index;

}

void InputMan::activate_event(const std::string& event_name) {

    auto& instance = InputMan::get_instance();

    size_t index = instance.get_event_index(event_name);

    if (m_input_buffer.buffer_end < buffer_size){
        m_input_buffer.active_buffer[m_input_buffer.buffer_end] = index;
        ++m_input_buffer.buffer_end;
    }

}

void InputMan::flush_active_buffer(){

    auto& instance = InputMan::get_instance();

    instance.m_input_buffer.buffer_end = 0;

}
