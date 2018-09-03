#include "search_engine.h"
#include "SearchEngine.h"

void search_init(const char *dictionary_db_dir_path, const char *dictionary_db_name)
{
    SearchEngine::Core::SearchEngineImpl::Instance().Init(dictionary_db_dir_path, dictionary_db_name);
}

void search_for(const char *word) 
{
    SearchEngine::Core::SearchEngineImpl::Instance().Search(word);
}

vector<string> search_get_result()
{
    return SearchEngine::Core::SearchEngineImpl::Instance().GetResult();
}

map<string, vector<string>> get_translate(int word_id)
{
    return SearchEngine::Core::SearchEngineImpl::Instance().GetTranslate(word_id);
}