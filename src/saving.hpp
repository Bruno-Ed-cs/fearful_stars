#pragma once 

#include "deps.hpp"

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
