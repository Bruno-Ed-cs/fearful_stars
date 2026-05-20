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

string key_encode(string type, string id, string member) {

    return std::format("{}:{}:{}", type, id, member);

}

std::map<string, string> key_decode(string key) {

    std::map<string, string> decoded;

    for (std::size_t i = 0, token_init = 0, token_num = 1; i < key.size(); ++i) {
        if (key[i] == ':') {

            switch (token_num) {

                case 1:
                    decoded["type"] = string(key, token_init, i - 1);
                break;

                case 2:
                    decoded["id"] = string(key, token_init, i - 1);
                break;

                case 3:
                    decoded["member"] = string(key, token_init, i - 1);
                break;

                defaut:
                    break;

            }
            token_init = i + 1;
            token_num++;

        }
    }

    return decoded;

}
