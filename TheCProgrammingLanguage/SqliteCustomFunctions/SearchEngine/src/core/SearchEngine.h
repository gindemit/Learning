#pragma once
#include "QueryExecutor.h"

#include <sqlite3.h>

#include <map>
#include <vector>
#include <string>


namespace SearchEngine::Core
{
    using ::std::map;
    using ::std::vector;
    using ::std::string;

    class SearchEngineImpl {
    private:
        sqlite3 *_db = nullptr;
        QueryExecutor *_queryExecutor = nullptr;

    public:
        ~SearchEngineImpl();
        SearchEngineImpl(SearchEngineImpl const&) = delete;
        void operator=(SearchEngineImpl const&) = delete;
        static SearchEngineImpl& Instance();

        void Init(const char *dictionaryDirDbPath, const char *dictionaryDbName);
        void Search(const char *word);
        vector<string> GetResult();
        map<string, vector<string>> GetTranslate(int wordId);

    private:
        SearchEngineImpl() {}
        void ValidateDbPath(const string fullPath) const;
        void OpenDataBase(const char *dbPath, sqlite3 **database);
    };
}