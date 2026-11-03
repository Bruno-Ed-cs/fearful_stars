#pragma once
#include "deps.hpp"


struct DamageSource {

    int m_base_damage = 0;
    int m_damage_pool = 0;
    int m_hit_count = 0; // counts the whole lifetime
    int m_max_pool = 0;
    bool m_locked = false;

    enum struct Mode {
        INFINITE,
        LIMITED,
    } m_mode = Mode::LIMITED;

    DamageSource() = default;
    DamageSource(Mode mode, int base_damage, int damage_pool = 0, int damage_pool_ceiling = 0) : DamageSource() {
         
        m_mode = mode;
        m_base_damage = base_damage;
        m_damage_pool = damage_pool;
        m_max_pool = damage_pool_ceiling;
    }

    //core method
    int extract() {

        int damage = 0;

        switch (m_mode) {
            
        case Mode::LIMITED: {

            int original = m_damage_pool;
            m_damage_pool -= m_base_damage;
            m_damage_pool = std::clamp(m_damage_pool, 0, m_max_pool);
            damage = original - m_damage_pool;

        } break;

        case Mode::INFINITE: {
            damage = m_base_damage;

        } break;

        }

        return damage;

    }

    bool is_empty() {

        if (m_damage_pool <= 0)
            return true;

        return false;

    }

    int refresh(int damage) {

        int original = m_damage_pool;
        m_damage_pool += damage;
        m_damage_pool = std::clamp(m_damage_pool, 0, m_max_pool);

        return m_damage_pool - original;

    }

    int refresh() {

        int original = m_damage_pool;
        m_damage_pool = m_max_pool;

        return m_damage_pool - original;
    }

    void open() {
        m_locked = false;
    }

    void close() {
        m_locked = true;
    }

    bool available() { 
        return !m_locked;
    }

};

struct DamagePool {

    int m_damage_pool = 0;
    int m_hit_count = 0;
    bool m_locked = false;

    enum struct Mode {
        BINARY,
        CUMULATIVE,
    } m_mode = Mode::CUMULATIVE;

    DamagePool() = default;
    DamagePool(Mode mode) : DamagePool() {
        m_mode = mode;
    }

    //core method
    int input(int damage) {

        int input = 0;

        switch(m_mode) {
        
        case Mode::BINARY: {
            input = 1;

        } break;

        case Mode::CUMULATIVE: {
            input = damage;

        } break;

        }

        m_damage_pool += input;
        return input;

    }

    bool is_empty() {
        if (m_damage_pool <= 0) 
            return true;

        return false;
    }

    int drain() {
        int value = m_damage_pool;

        m_damage_pool = 0;

        return value;

    }

    void close() {
        m_locked = true;
    }
    void open() {
        m_locked = false;
    }

    bool available() {
        return m_locked;
    }

};
