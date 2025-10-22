#include "asset_man.hpp"
#include "raylib.h"
#include <print>
#include <string_view>

using namespace Engine;

template<typename T>
using sptr = std::shared_ptr<T>;

std::list<AssetMan::AssetContainer<Texture>> AssetMan::texture_bank;
std::list<AssetMan::AssetContainer<Sound>> AssetMan::sound_bank;
std::list<AssetMan::AssetContainer<Music>> AssetMan::music_bank;
std::list<AssetMan::AssetContainer<Font>> AssetMan::font_bank;
std::list<AssetMan::AssetContainer<Shader>> AssetMan::shader_bank;

using str_par = std::string_view;

static std::string search_asset(str_par base_dir, str_par asset_name, str_par filter) {

    std::string app_dir = GetApplicationDirectory();
    std::println("{}", app_dir);
    std::string asset_dir = std::string(app_dir) + std::string(base_dir);
    std::println("{}", asset_dir);

    FilePathList files = LoadDirectoryFilesEx(asset_dir.c_str(), std::string(filter).c_str(), true);

    if (files.count <= 0)
        throw std::invalid_argument(std::format("The Asset {} could not be found", asset_name));

    std::string target_path;
    std::string buff;

    for (int i = 0; i < files.count; ++i) {

        buff = files.paths[i];

        if (buff.contains(asset_name)) {

            target_path = buff;
            break;

        }
    }

    if (target_path.empty())
        throw std::invalid_argument(std::format("The Asset {} could not be found", asset_name));

    return target_path;

}

sptr<Shader> AssetMan::get_shader(std::string_view shader_name) {

    auto search_iter = std::find_if(shader_bank.begin(), shader_bank.end(), 
    [shader_name](const AssetContainer<Shader>& container) {

    return container.name == shader_name;
    });

    if (search_iter != shader_bank.end()) {

        return search_iter->asset_origin;
    }

    std::string search_result_vert = search_asset("assets/shaders", shader_name, ".vert");
    std::string search_result_frag = search_asset("assets/shaders", shader_name, ".frag");

    Shader* shader_ptr = new Shader;
    *shader_ptr = LoadShader(search_result_vert.c_str(), search_result_frag.c_str());

    auto shader_ref = sptr<Shader>(shader_ptr, ShaderDestroyer{});
    shader_bank.emplace_front(std::string(shader_name), shader_ref);

    return shader_ref;

};

sptr<Texture> AssetMan::get_texture(const str& texture_name){

    auto search_iter = std::find_if(texture_bank.begin(), texture_bank.end(), 
    [texture_name](const AssetContainer<Texture>& container) {

        return container.name == texture_name;

    });

    if (search_iter != texture_bank.end()) {

        return search_iter->asset_origin;
    }

    std::string search_result = search_asset("assets/sprites", texture_name, ".png");

    Texture* texture_ptr = new Texture;
    *texture_ptr = LoadTexture(search_result.c_str());

    auto texture_reference = sptr<Texture>(texture_ptr, TextureDestroyer{});
    texture_bank.emplace_front(texture_name, texture_reference);

    return texture_reference;
}

sptr<Music> AssetMan::get_music(const str& music_name){

    auto search_iter = std::find_if(music_bank.begin(), music_bank.end(), 
    [music_name](const AssetContainer<Music>& container) {

        return container.name == music_name;

    });

    if (search_iter != music_bank.end()) {

        return search_iter->asset_origin;
    }

    std::string search_result = search_asset("assets/musics", music_name, ".mp3");

    Music* music_ptr = new Music;
    *music_ptr = LoadMusicStream(search_result.c_str());

    auto music_reference = sptr<Music>(music_ptr, MusicDestroyer{});
    music_bank.emplace_front(music_name, music_reference);

    return music_reference;
}

sptr<Sound> AssetMan::get_sound(const str& sound_name){

    auto search_iter = std::find_if(sound_bank.begin(), sound_bank.end(), 
    [sound_name](const AssetContainer<Sound>& container) {

        return container.name == sound_name;

    });

    if (search_iter != sound_bank.end()) {

        return search_iter->asset_origin;
    }

    std::string search_result = search_asset("assets/sounds", sound_name, ".wav;.ogg;.mp3");

    Sound* sound_ptr = new Sound;
    *sound_ptr = LoadSound(search_result.c_str());

    auto sound_reference = sptr<Sound>(sound_ptr, SoundDestroyer{});
    sound_bank.emplace_front(sound_name, sound_reference);

    return sound_reference;
}

sptr<Font> AssetMan::get_font(const str& font_name){

    auto search_iter = std::find_if(font_bank.begin(), font_bank.end(), 
    [font_name](const AssetContainer<Font>& container) {

        return container.name == font_name;

    });

    if (search_iter != font_bank.end()) {

        return search_iter->asset_origin;
    }

    std::string search_result = search_asset("assets/fonts", font_name, ".otf;.ttf");

    Font* font_ptr = new Font;
    *font_ptr = LoadFont(search_result.c_str());

    auto font_reference = sptr<Font>(font_ptr, FontDestroyer{});
    font_bank.emplace_front(font_name, font_reference);

    return font_reference;
}

void AssetMan::preload_shaders(std::initializer_list<std::string_view> shaders) {

    for (auto shader_name : shaders) {

        AssetMan::get_shader(shader_name);
    }

};

void AssetMan::InitAssetManager(){

    music_bank = std::list<AssetContainer<Music>>();
    texture_bank = std::list<AssetContainer<Texture>>();
    sound_bank = std::list<AssetContainer<Sound>>();
    font_bank = std::list<AssetContainer<Font>>();
    shader_bank = std::list<AssetContainer<Shader>>();
}

void AssetMan::cleanup() {

    texture_bank.remove_if([](AssetContainer<Texture>& container){ return container.asset_origin.use_count() <= 1; });
    music_bank.remove_if([](AssetContainer<Music>& container){ return container.asset_origin.use_count() <= 1; });
    sound_bank.remove_if([](AssetContainer<Sound>& container){ return container.asset_origin.use_count() <= 1; });
    font_bank.remove_if([](AssetContainer<Font>& container){ return container.asset_origin.use_count() <= 1; });

}

void AssetMan::empty_out() {

    texture_bank.clear();
    music_bank.clear();
    sound_bank.clear();
    font_bank.clear();

}
