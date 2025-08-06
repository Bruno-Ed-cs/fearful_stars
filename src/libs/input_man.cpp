#include "input_man.hpp"

using namespace engine;

void InputMan::pull_events() {



}// call at the beggining of the game loop;

void InputMan::flush_events() {

}// call at the end of the game loop;

bool InputMan::in_event_active(const std::string& event_name){ 

}

void InputMan::load_events(const std::vector<Event>& events) {

}

void InputMan::add_input_to_event(const std::string& event_name, const int new_input) {

}


void InputMan::close() {

}

size_t InputMan::get_event_index(const std::string& event_name) {

    size_t index = 0;
    bool found = false;

    for (size_t i = 0; i < m_event_pool.size(); ++i) {

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
