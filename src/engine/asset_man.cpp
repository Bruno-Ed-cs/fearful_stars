#include "asset_man.hpp"
#include "raylib.h"
#include <print>
#include <string_view>

using namespace Engine;

template<typename T>
using sptr = std::shared_ptr<T>;

using str_view = std::string_view;
using str = std::string;

static str search_asset(str_view base_dir, str_view asset_name, str_view filter) {

    str app_dir = GetApplicationDirectory();
    std::println("{}", app_dir);
    str asset_dir = str(app_dir) + str(base_dir);
    std::println("{}", asset_dir);

    FilePathList files = LoadDirectoryFilesEx(asset_dir.c_str(), str(filter).c_str(), true);

    if (files.count <= 0)
        throw std::invalid_argument(std::format("The Asset {} could not be found", asset_name));

    str target_path;
    str buff;

    for (int i = 0; i < files.count; ++i) {

        buff = files.paths[i];

        if (buff.contains(asset_name)) {

            target_path = buff;
            break;

        }
    }

    if (target_path.empty())
        throw std::invalid_argument(std::format("The Asset {} could not be found", asset_name));

    UnloadDirectoryFiles(files);
    return target_path;

}

sptr<Shader> AssetMan::get_shader(str_view shader_name) {

    if (shader_bank.contains(str(shader_name))) {

        return shader_bank[str(shader_name)];
    }

    str search_result_vert = search_asset("assets/shaders", shader_name, ".vert");
    str search_result_frag = search_asset("assets/shaders", shader_name, ".frag");

    Shader* shader_ptr = new Shader;
    *shader_ptr = LoadShader(search_result_vert.c_str(), search_result_frag.c_str());

    auto shader_ref = sptr<Shader>(shader_ptr, ShaderDestroyer{});
    shader_bank.emplace(std::pair(str(shader_name), shader_ref));

    return shader_ref;

};

sptr<Texture> AssetMan::get_texture(const str& texture_name){

    if (texture_bank.contains(str(texture_name))) {

        return texture_bank[str(texture_name)];
    }

    str search_result = search_asset("assets/sprites", texture_name, ".png");

    Texture* texture_ptr = new Texture;
    *texture_ptr = LoadTexture(search_result.c_str());

    auto texture_reference = sptr<Texture>(texture_ptr, TextureDestroyer{});
    texture_bank.emplace(str(texture_name), texture_reference);

    return texture_reference;
}

sptr<Music> AssetMan::get_music(const str& music_name){

    if (music_bank.contains(str(music_name))) {

        return music_bank[str(music_name)];
    }

    str search_result = search_asset("assets/musics", music_name, ".mp3");

    Music* music_ptr = new Music;
    *music_ptr = LoadMusicStream(search_result.c_str());

    auto music_reference = sptr<Music>(music_ptr, MusicDestroyer{});
    music_bank.emplace(str(music_name), music_reference);

    return music_reference;
}

sptr<Sound> AssetMan::get_sound(const str& sound_name){

    if (sound_bank.contains(str(sound_name))) {

        return sound_bank[str(sound_name)];
    }

    str search_result = search_asset("assets/sounds", sound_name, ".wav;.ogg;.mp3");

    Sound* sound_ptr = new Sound;
    *sound_ptr = LoadSound(search_result.c_str());

    auto sound_reference = sptr<Sound>(sound_ptr, SoundDestroyer{});
    sound_bank.emplace(str(sound_name), sound_reference);

    return sound_reference;
}

sptr<Font> AssetMan::get_font(const str& font_name){

    if (font_bank.contains(str(font_name))) {

        return font_bank[str(font_name)];
    }

    str search_result = search_asset("assets/fonts", font_name, ".otf;.ttf");

    Font* font_ptr = new Font;
    *font_ptr = LoadFontEx(search_result.c_str(), 600, NULL, 0);

    auto font_reference = sptr<Font>(font_ptr, FontDestroyer{});
    font_bank.emplace(str(font_name), font_reference);

    return font_reference;
}
void AssetMan::preload_shaders(std::initializer_list<str_view> shaders) {

    for (auto shader_name : shaders) {

        AssetMan::get_shader(shader_name);
    }

};

void AssetMan::init(){

    music_bank =    std::unordered_map<str, sptr<Music>>();
    texture_bank =  std::unordered_map<str, sptr<Texture>>();
    sound_bank =    std::unordered_map<str, sptr<Sound>>();
    font_bank =     std::unordered_map<str, sptr<Font>>();
    shader_bank =   std::unordered_map<str, sptr<Shader>>();
}

void AssetMan::cleanup() {

    for (auto it = texture_bank.begin(); it != texture_bank.end();) {

        if (it->second.use_count() <= 1) 
        {
            it = texture_bank.erase(it);
        } else {

            ++it;
        }

    }

    for (auto it = music_bank.begin(); it != music_bank.end();) {

        if (it->second.use_count() <= 1) 
        {
            it = music_bank.erase(it);
        } else {

            ++it;
        }

    }
    for (auto it = sound_bank.begin(); it != sound_bank.end();) {

        if (it->second.use_count() <= 1) 
        {
            it = sound_bank.erase(it);
        } else {

            ++it;
        }

    }
    for (auto it = font_bank.begin(); it != font_bank.end();) {

        if (it->second.use_count() <= 1) 
        {
            it = font_bank.erase(it);
        } else {

            ++it;
        }

    }
}

void AssetMan::empty_out() {

    texture_bank.clear();
    music_bank.clear();
    sound_bank.clear();
    font_bank.clear();

}
