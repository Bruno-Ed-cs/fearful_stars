#include "background_man.hpp"
#include "entity.hpp"
#include "id_generator.hpp"
#include "render_man.hpp"
#include "asset_man.hpp"
#include "saving.hpp"

using namespace Engine;

void BackgroundMan::init() {

    element_bank = std::vector<ElementContainer>();

}

uint32_t BackgroundMan::make_element(const std::string& sprite_name,
                                       Rectangle source,
                                       Rectangle projection,
                                       Game::Position initial_pos,
                                       double speed,
                                       double rotation,
                                       int z_index,
                                       BackgroundElement::Fn mode) {

    mode_func mode_fn;

    switch (mode) {
        case BackgroundElement::Fn::across:
            mode_fn = BackgroundElement::Mode::across;
        break;

        case BackgroundElement::Fn::loop:
            mode_fn = BackgroundElement::Mode::loop;
        break;

        case BackgroundElement::Fn::stay:
            mode_fn = BackgroundElement::Mode::stay;
        break;

    }

    BackgroundElement element{
        .canva_location = initial_pos,
        .sprite_name = sprite_name,
        .sprite = AssetMan::get_texture(sprite_name),
        .source = source,
        .projection = projection,
        .rotation = rotation,
        .speed = speed,
        .z_index = z_index,
        .mode = mode_fn,
        .mode_id = mode
    };

    uint32_t id = generate_id<BackgroundMan>([](uint32_t id){

        for (auto& container: element_bank) {

            if (container.id == id) {
                return true;
            }

        };
        return false;

    });

    element_bank.push_back(ElementContainer{
        .id = id,
        .element = element});

    return id;
}

void BackgroundMan::clear_background() {

    element_bank.clear();

}

void BackgroundMan::remove_element(uint32_t id) {

    for (int i = 0; i < element_bank.size(); ++i) {

        if (element_bank[i].id == id) {

            element_bank.erase(element_bank.begin() + i);

        }

    }

}

void BackgroundMan::update(double dt) {

    static std::vector<bool> element_status;
    element_status.reserve(element_bank.size());

    for (auto& container : element_bank) {

        element_status.push_back(container.element.mode(container.element, dt));
    }

    for (int i = 0; i < element_status.size(); ++i) {

        if (element_status[i] == false) {

            remove_element(element_bank[i].id);
        }

    }

    element_status.clear();
}

void BackgroundMan::draw() {

    for (auto& container : element_bank) {

        Texture sprite = *container.element.sprite;

        RenderMan::send_texture(
            RenderMan::Plane::back,
            sprite,
            container.element.projection,
            container.element.source,
            0,
            container.element.rotation);

    }

}

bool BackgroundElement::Mode::stay(BackgroundElement& element, double dt) {

    element.projection.x = element.canva_location.x;
    element.projection.y = element.canva_location.y;
    return true;
}

bool BackgroundElement::Mode::across(BackgroundElement& element, double dt) {
    return false;
}

bool BackgroundElement::Mode::loop(BackgroundElement& element, double dt) {
    return false;
}

void BackgroundMan::save_background(Engine::GameState &sys) {

    if (sys.save_slot == 0) return;

    clean_by_prefix(sys, "Background");

    for (auto& capsule: element_bank) {
        
        Engine::Package pack = capsule.element.package();

        for (auto& line: pack) {

            std::string key = key_encode("Background", 1, capsule.id, line.first);

            sys.save_connection->Put(rocksdb::WriteOptions(), key, line.second);

        }

    }
}

void BackgroundMan::load_background(Engine::GameState& sys) {

    element_bank.clear();
    
    std::vector<int> identifiers;
    identifiers.reserve(50);

    std::unique_ptr<rocksdb::Iterator> it(sys.save_connection->NewIterator(rocksdb::ReadOptions()));

    for (it->Seek("Background"); it->Valid() && it->key().starts_with("Background"); it->Next()) {
        
        bool exist = false;
        auto parsed_key = key_decode(it->key().ToString());

        for (int i = 0; i < identifiers.size(); ++i) {

            if (std::stoi(parsed_key["id"]) == identifiers[i]) {

                exist = true;
                break;
            }

        }

        if (!exist) {
            identifiers.push_back(std::stoi(parsed_key["id"]));
        }

    }

    it->Reset();

    for (auto& id: identifiers) {

        Engine::Package pack;

        std::string prefix = std::format("Background:1:{}", id);


        for (it->Seek(prefix); it->Valid() && it->key().starts_with(prefix); it->Next()) {

            std::string member = key_decode(it->key().ToString())["member"];

            pack[member] = it->value().ToString();

        }

        std::string sprite_name = pack["sprite_name"];
        double speed = std::stod(pack["speed"]);
        double rotation = std::stod(pack["rotation"]);
        int z_index = std::stoi(pack["z_index"]);
        auto mode = BackgroundElement::Fn(std::stoi(pack["mode"]));

        Rectangle source = {
            .x = std::stof(pack["source_x"]),
            .y = std::stof(pack["source_y"]),
            .width = std::stof(pack["source_width"]),
            .height = std::stof(pack["source_height"]),
        };
        Rectangle projection = {

            .x = std::stof(pack["projection_x"]),
            .y = std::stof(pack["projection_y"]),
            .width = std::stof(pack["projection_width"]),
            .height = std::stof(pack["projection_height"]),
        };
        Game::Position initial_pos = {
            std::stof(pack["canva_location_x"]),
            std::stof(pack["canva_location_y"]),
        };

        BackgroundMan::make_element(sprite_name, source, projection, initial_pos, speed, rotation, z_index, mode);

    }

}


