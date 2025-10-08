#include "asset_man.hpp"
#include <print>
#include <string_view>

using namespace Engine;

template<typename T>
using sptr = std::shared_ptr<T>;

std::list<AssetMan::AssetContainer<Texture>> AssetMan::texture_bank;
std::list<AssetMan::AssetContainer<Sound>> AssetMan::sound_bank;
std::list<AssetMan::AssetContainer<Music>> AssetMan::music_bank;
std::list<AssetMan::AssetContainer<Font>> AssetMan::font_bank;

using str_par = const std::string&;

static std::string search_asset(str_par base_dir, str_par asset_name, str_par filter) {

    std::string app_dir = GetApplicationDirectory();
    std::println("{}", app_dir);
    std::string asset_dir = app_dir + base_dir;
    std::println("{}", asset_dir);

    FilePathList files = LoadDirectoryFilesEx(asset_dir.c_str(), filter.c_str(), true);

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

//sptr<Music> AssetMan::get_music(const str& music_name){
//
//}
//
//sptr<Sound> AssetMan::get_sound(const str& sound_name){
//
//}
//
//sptr<Font> AssetMan::get_font(const str& font_name){
//
//}

void AssetMan::InitAssetManager(){

    music_bank = std::list<AssetContainer<Music>>();
    texture_bank = std::list<AssetContainer<Texture>>();
    sound_bank = std::list<AssetContainer<Sound>>();
    font_bank = std::list<AssetContainer<Font>>();

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
