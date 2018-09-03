#include "QueryExecutor.h"
#include "Exception/QueryExecException.h"

#include <sstream>

namespace SearchEngine::Core
{
    QueryExecutor::QueryExecutor(sqlite3 *db) :
        _db(db)
    {
        AttachDataBases();
        CreateTablesIfNeeded();
    }
    QueryExecutor::~QueryExecutor()
    {

    }

    void QueryExecutor::Search(const char *word)
    {
        ::std::stringstream query;
        query << "DELETE FROM results.lastsearch; INSERT INTO results.lastsearch SELECT idWord, name FROM word WHERE name LIKE '";
        query << word;
        query << "';";
        QueryExec(query.str().c_str());
    }

    int GetLastSearchResultCallback(void *vectorString, int argc, char **argv, char **azColName)
    {
        vector<string> *result = (vector<string>*)(vectorString);
        result->emplace_back(argv[0]);
        return 0;
    }

    vector<string> QueryExecutor::GetLastSearchResult()
    {
        vector<string> result;

        char *err = nullptr;
        if (sqlite3_exec(_db, "SELECT name FROM results.lastsearch", GetLastSearchResultCallback, &result, &err))
        {
            ::std::string error_copy(err);
            sqlite3_free(err);
            throw Exception::QueryExecException(error_copy);
        }

        return result;
    }


    void QueryExecutor::AttachDataBases()
    {
        QueryExec("ATTACH 'results.db' AS results;");
        QueryExec("ATTACH 'userdata.db' AS userdata;");
    }

    void QueryExecutor::CreateTablesIfNeeded()
    {
        QueryExec("CREATE TABLE IF NOT EXISTS results.lastsearch(idWord INTEGER, name VARCHAR2(255), PRIMARY KEY (idWord ASC));");
    }

    void QueryExecutor::QueryExec(const char *query)
    {
        char *err = nullptr;
        if (sqlite3_exec(_db, query, nullptr, nullptr, &err))
        {
            ::std::string error_copy(err);
            sqlite3_free(err);
            throw Exception::QueryExecException(error_copy);
        }
    }
}