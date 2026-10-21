#pragma once

#include "deps.hpp"

namespace Engine {

using MusicRef = std::shared_ptr<Music>;
using SoundRef = std::shared_ptr<Sound>;
template<typename T>
using vector = std::vector<T>;

class MusicMan {

public:

    enum class Mode {
        loop,
        one_shot,
        playlist
    };

    static void init();
    static void update();
    static void add_music_to_buffer(MusicRef music_ref);
    static void set_mode(Mode mode);
    static void clean();
    static void set_pitch(double pitch);
    static void reset_pitch();
    static void set_volume(double volume);
    static void reset_volumet();
    static void play_sfx(SoundRef sfx_ptr);

    static void start_music();
    static void stop_music();

private:

    static void loop();
    static void one_shot();
    static void playlist();

private:

    inline static vector<MusicRef> m_buffer;
    inline static double m_volume;
    inline static double m_pitch;
    inline static Mode m_cur_mode;
};

}
