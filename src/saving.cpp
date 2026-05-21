#include "deps.hpp"
#include "rocksdb/db.h"
#include "saving.hpp"

using string = std::string;

string get_save_dir() {

    const string appdir = GetApplicationDirectory();
    string savedir = appdir + std::string("/saves");

    if (!DirectoryExists(savedir.c_str())) {
        if (!MakeDirectory(savedir.c_str())) {
            std::println(stderr, "[Dir_Error] it was not possible to create the save directory");

            return std::string("");

        }
    }

    return savedir;

}

std::unique_ptr<rocksdb::DB> get_save_db(size_t save_slot) {

    string savedir = get_save_dir();
    string slotdir = std::format("{}/{}", get_save_dir(), save_slot);

    std::unique_ptr<rocksdb::DB> db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status;

    if (!savedir.empty())
        status = rocksdb::DB::Open(options, slotdir, &db);

    if (!status.ok()) std::cerr << status.ToString() << std::endl;

    return std::move(db);

}

string key_encode(string type, uint32_t subtype, uint32_t id, string member) {

    return std::format("{}:{}:{}:{}", type, subtype, id, member);

}

std::map<string, string> key_decode(string key) {

    std::map<string, string> decoded;
    std::vector<std::size_t> separators;

    for (int i = 0; i < key.size(); ++i) {

        if (key[i] == ':') {

            separators.push_back(i);

        }
    }

    //std::println("separators = {}", separators);
    decoded["type"] = string(key, 0, separators[0]);
    decoded["subtype"] = string(key, separators[0] + 1, (separators[1] - separators[0]) -1);
    decoded["id"] = string(key, separators[1] +1, (separators[2] - separators[1]) -1);
    decoded["member"] = string(key, separators[2] +1, (key.size() - separators[2]) - 1);

    return decoded;

}
