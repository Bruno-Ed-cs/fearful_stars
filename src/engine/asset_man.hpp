#pragma once

#include "deps.hpp"
#include "json.hpp"
#include "raylib.h"
#include <string_view>

template<typename T>
using sptr = std::shared_ptr<T>;
using string = std::string;
using json = nlohmann::json;
using string_view = std::string_view;

namespace Engine {

class AssetMan {


public:

    enum struct CurrentlyLoading {
        TEXTURES,
        MUSICS,
        SOUNDS,
        FONTS,
        ANIMATIONS,
        JSON,
        SHADERS
    };

    static Texture get_texture(std::string_view texture_name);
    static Music get_music(std::string_view music_name);
    static Sound get_sound(std::string_view sound_name);
    static Font get_font(std::string_view font_name);
    static sptr<json> get_animation(std::string_view animation_name);
    static sptr<json> get_json(std::string_view json_name);
    static Shader get_shader(std::string_view shader_name);

    static void preload_shaders(std::initializer_list<std::string_view>);
    static void load_all();
    static string_view load_all_stepped(int* step);

    static void init();
    static void cleanup();

public:

    struct FileTypes{

        enum struct Type {

            sprite,
            music,
            sound,
            font,
            shader,

        } type;

        const string_view* extensions;

    };

private:

    struct ShaderDestroyer {

        void operator()(Shader* ptr) {
            UnloadShader(*ptr);
        };

    };

    struct TextureDestroyer {

        void operator()(Texture* texture_ptr) {

            UnloadTexture(*texture_ptr);
        }

    };

    struct SoundDestroyer {

        void operator()(Sound* sound_ptr) {

            UnloadSound(*sound_ptr);
        }

    };

    struct MusicDestroyer {

        void operator()(Music* music_ptr) {

            UnloadMusicStream(*music_ptr);
        }

    };

    struct FontDestroyer {

        void operator()(Font* font_ptr) {

            UnloadFont(*font_ptr);

        }

    };

    inline static std::unordered_map<string, sptr<Texture>> texture_bank;
    inline static std::unordered_map<string, sptr<Sound>> sound_bank;
    inline static std::unordered_map<string, sptr<Music>> music_bank;
    inline static std::unordered_map<string, sptr<Font>> font_bank;
    inline static std::unordered_map<string, sptr<Shader>> json_name;
    inline static std::unordered_map<string, sptr<json>> json_bank;

};

}
