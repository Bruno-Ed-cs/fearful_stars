export module timer;

namespace Engine {

export class Timer {
public:
    Timer() = default;
    
    Timer(double seconds) 
        : m_time(seconds), m_limit(seconds) {}

    void set_limit(double seconds) { m_limit = seconds; }
    
    void update(double dt) {
        if (m_time < 0)
            m_time = 0;
        else 
            m_time -= dt;
    }

    bool past_limit() const { 
        return m_time <= 0;
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

    double get_time() const {
        return m_time;
    }

private:
    double m_time = 0.0;
    double m_limit = 0.0;
};

} // namespace Engine
