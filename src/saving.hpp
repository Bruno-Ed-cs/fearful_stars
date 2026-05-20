#pragma once 

#include "deps.hpp"
#include "rocksdb/db.h"

using string = std::string;

string get_save_dir();

std::unique_ptr<rocksdb::DB> get_save_db(size_t save_slot); 

string key_encode(string type, string id, string member); 

std::map<string, string> key_decode(string key); 
