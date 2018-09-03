#pragma once
#include "sqlite3.h"

#include <vector>
#include <string>

namespace SearchEngine::Core
{
    using ::std::vector;
    using ::std::string;

    class QueryExecutor {
    private:
        sqlite3 * _db;
    public:
        QueryExecutor(sqlite3 *db);
        ~QueryExecutor();
        void Search(const char *word);
        vector<string> GetLastSearchResult();

    private:
        void AttachDataBases();
        void CreateTablesIfNeeded();
        void QueryExec(const char *query);
    };
}