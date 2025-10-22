#pragma once

#include "deps.hpp"
#include "raylib.h"

namespace Engine {

class AssetMan {

template<typename T>
using sptr = std::shared_ptr<T>;
using str = std::string;

public:

    static sptr<Texture> get_texture(const str& texture_name);
    static sptr<Music> get_music(const str& music_name);
    static sptr<Sound> get_sound(const str& sound_name);
    static sptr<Font> get_font(const str& font_name);
    static sptr<Shader> get_shader(std::string_view shader_name);

    static void preload_shaders(std::initializer_list<std::string_view>);

    static void InitAssetManager();
    static void cleanup();
    static void empty_out();

private:

    template<typename Asset>
    struct AssetContainer {

        str name;
        sptr<Asset> asset_origin;

    };

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

    static std::list<AssetContainer<Texture>> texture_bank;
    static std::list<AssetContainer<Sound>> sound_bank;
    static std::list<AssetContainer<Music>> music_bank;
    static std::list<AssetContainer<Font>> font_bank;
    static std::list<AssetContainer<Shader>> shader_bank;

};

}
