#pragma once

namespace engine {

class Timer {

public:

    Timer() {}

    Timer(double limit) :
    m_time(0.0f), m_limit(limit) {}

    void set_limit(double seconds) { m_limit = seconds; }
    void update(double dt) {
        m_time += dt;
    }

    bool past_limit() { 

        if (m_limit < m_time) 
            return true;
        else {
            return false;
        }

    }

    void reset() { m_time = 0.0f; }

    void reset(double new_limit) { 
        m_time = 0.0f;
        m_limit = new_limit;
    }
        


    bool loop() { 
        if (past_limit()) {

            m_time = 0.0f;
            return true;

        } else {

            return false;
        }
    }


private:

    double m_time = 0.0f;
    double m_limit = 0.0f;

};

}
