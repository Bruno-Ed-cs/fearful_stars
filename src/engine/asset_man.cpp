#include "asset_man.hpp"
#include "raylib.h"
#include "defer.hpp"
#include <print>
#include <string_view>

using namespace Engine;

static string search_asset(string_view base_dir, string_view asset_name, string_view filter) {

    string app_dir = GetApplicationDirectory();
    // std::println("{}", app_dir);
    string asset_dir = string(app_dir) + string(base_dir);
    // std::println("{}", asset_dir);

    FilePathList files = LoadDirectoryFilesEx(asset_dir.c_str(), string(filter).c_str(), true);
    defer(UnloadDirectoryFiles(files));

    if (files.count <= 0)
        throw std::invalid_argument(std::format("The Asset {} could not be found", asset_name));

    string target_path;
    string buff;

    for (int i = 0; i < files.count; ++i) {

        buff = files.paths[i];
        // std::println("{}, asset_name: {}", buff, asset_name);
        TraceLog(LOG_DEBUG, std::format("Searching file: {}, target: {}", buff, asset_name).c_str());

        if (buff.contains(std::format("/{}.", asset_name))) {

            target_path = buff;
            break;

        }
    }

    if (target_path.empty())
        throw std::invalid_argument(std::format("The Asset {} could not be found", asset_name));

    return target_path;

}

sptr<Shader> AssetMan::get_shader(string_view shader_name) {

    if (json_name.contains(string(shader_name))) {

        return json_name[string(shader_name)];
    }

    string search_result_vert = search_asset("assets/shaders", shader_name, ".vert");
    string search_result_frag = search_asset("assets/shaders", shader_name, ".frag");

    Shader* shader_ptr = new Shader;
    *shader_ptr = LoadShader(search_result_vert.c_str(), search_result_frag.c_str());

    auto shader_ref = sptr<Shader>(shader_ptr, ShaderDestroyer{});
    json_name.emplace(std::pair(string(shader_name), shader_ref));

    return shader_ref;

};

sptr<Texture> AssetMan::get_texture(std::string_view texture_name){

    if (texture_bank.contains(string(texture_name))) {

        return texture_bank[string(texture_name)];
    }

    string search_result = search_asset("assets/sprites", texture_name, ".png");

    Texture* texture_ptr = new Texture;
    *texture_ptr = LoadTexture(search_result.c_str());

    auto texture_reference = sptr<Texture>(texture_ptr, TextureDestroyer{});
    texture_bank.emplace(string(texture_name), texture_reference);

    return texture_reference;
}

sptr<Music> AssetMan::get_music(std::string_view music_name){

    if (music_bank.contains(string(music_name))) {

        return music_bank[string(music_name)];
    }

    string search_result = search_asset("assets/musics", music_name, ".mp3");

    Music* music_ptr = new Music;
    *music_ptr = LoadMusicStream(search_result.c_str());

    auto music_reference = sptr<Music>(music_ptr, MusicDestroyer{});
    music_bank.emplace(string(music_name), music_reference);

    return music_reference;
}

sptr<Sound> AssetMan::get_sound(std::string_view sound_name){

    if (sound_bank.contains(string(sound_name))) {

        return sound_bank[string(sound_name)];
    }

    string search_result = search_asset("assets/sounds", sound_name, ".wav;.ogg;.mp3");

    Sound* sound_ptr = new Sound;
    *sound_ptr = LoadSound(search_result.c_str());

    auto sound_reference = sptr<Sound>(sound_ptr, SoundDestroyer{});
    sound_bank.emplace(string(sound_name), sound_reference);

    return sound_reference;
}

sptr<Font> AssetMan::get_font(std::string_view font_name){

    if (font_bank.contains(string(font_name))) {

        return font_bank[string(font_name)];
    }

    string search_result = search_asset("assets/fonts", font_name, ".otf;.ttf");

    Font* font_ptr = new Font;
    *font_ptr = LoadFontEx(search_result.c_str(), 600, NULL, 0);

    auto font_reference = sptr<Font>(font_ptr, FontDestroyer{});
    font_bank.emplace(string(font_name), font_reference);

    return font_reference;
}
void AssetMan::preload_shaders(std::initializer_list<string_view> shaders) {

    for (auto shader_name : shaders) {

        AssetMan::get_shader(shader_name);
    }

};

void AssetMan::init(){

    music_bank =    std::unordered_map<string, sptr<Music>>();
    texture_bank =  std::unordered_map<string, sptr<Texture>>();
    sound_bank =    std::unordered_map<string, sptr<Sound>>();
    font_bank =     std::unordered_map<string, sptr<Font>>();
    json_name =   std::unordered_map<string, sptr<Shader>>();
    json_bank =     std::unordered_map<string, sptr<json>>();
}

void AssetMan::cleanup() {


    for (auto it = texture_bank.begin(); it != texture_bank.end();) {

        it = texture_bank.erase(it);

    }

    for (auto it = music_bank.begin(); it != music_bank.end();) {

        it = music_bank.erase(it);

    }
    for (auto it = sound_bank.begin(); it != sound_bank.end();) {

        it = sound_bank.erase(it);

    }
    for (auto it = font_bank.begin(); it != font_bank.end();) {

        it = font_bank.erase(it);

    }

    for (auto it = json_bank.begin(); it != json_bank.end();) {

        it = json_bank.erase(it);

    }
}


sptr<json> AssetMan::get_animation(std::string_view animation_name) {

    if (json_bank.contains(string(animation_name))) {

        return json_bank[string(animation_name)];
    }

    string search_result = search_asset("assets/animations", animation_name, ".json");

    char* file = LoadFileText(search_result.c_str());
    defer(UnloadFileText(file));

    sptr<json> parsed {new json(json::parse(file))};

    json_bank.emplace(std::pair(string(animation_name), parsed));

    return parsed;

}

sptr<json> AssetMan::get_json(std::string_view json_name) {

    if (json_bank.contains(string(json_name))) {

        return json_bank[string(json_name)];
    }

    string search_result = search_asset("assets", json_name, ".json");

    char* file = LoadFileText(search_result.c_str());
    defer(UnloadFileText(file));

    sptr<json> parsed {new json(json::parse(file))};

    json_bank.emplace(std::pair(string(json_name), parsed));

    return parsed;


}

