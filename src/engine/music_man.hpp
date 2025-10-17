#pragma once

#include "deps.hpp"

namespace Engine {

using MusicRef = std::shared_ptr<Music>;
template<typename T>
using vector = std::vector<T>;

class MusicMan {

public:

    enum class Mode {
        loop,
        one_shot,
        playlist
    };

    MusicMan();
    void update();
    void add_music_to_buffer(MusicRef music_ref);
    void set_mode(Mode mode);
    void clean();
    void set_pitch(double pitch);
    void reset_pitch();
    void set_volume(double volume);
    void reset_volumet();

    void start_music();
    void stop_music();

private:

    void loop();
    void one_shot();
    void playlist();

private:

    vector<MusicRef> m_buffer;
    double m_volume;
    double m_pitch;
    Mode m_cur_mode;


};

}
