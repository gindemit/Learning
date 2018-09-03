#pragma once
#include <map>
#include <vector>
#include <string>

using ::std::map;
using ::std::vector;
using ::std::string;

void search_init(const char *dictionary_db_dir_path, const char *dictionary_db_name);

void search_for(const char *word);

vector<string> search_get_result();
map<string, vector<string>> get_translate(int word_id);