#pragma once

namespace Engine {

class Timer {

public:

    Timer() {}

    Timer(double limit) :
    m_time(0.0f), m_limit(limit) {}

    void set_limit(double seconds) { m_limit = seconds; }
    void update(double dt) {
        if (m_time <= 0)
            m_time = 0;
        else 
            m_time -= dt;
    }

    bool past_limit() { 

        if (m_time <= 0) 
            return true;
        else {
            return false;
        }

    }

    void reset() { m_time = m_limit; }

    void reset(double new_limit) { 

        m_limit = new_limit;
        m_time = m_limit;
    }
        


    bool loop() { 
        if (past_limit()) {

            m_time = m_limit;
            return true;

        } else {

            return false;
        }
    }

    float get_time() {

        return m_time;
    }

private:

    double m_time = 0.0f;
    double m_limit = 0.0f;

};

}
