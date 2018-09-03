#include "SearchEngine.h"
#include "sqlite3/nusqlite3.h"

#include "Exception/OpenDbException.h"
#include "Exception/InvalidDbPathException.h"

namespace SearchEngine::Core
{
    SearchEngineImpl& SearchEngineImpl::Instance() {
        static SearchEngineImpl impl;
        return impl;
    }

    void SearchEngineImpl::Init(const char *dictionaryDirDbPath, const char *dictionaryDbName)
    {
        string dirPath(dictionaryDirDbPath);
        string fileName(dictionaryDbName);
        string dictionaryFullPath = dirPath + "/" + fileName;

        ValidateDbPath(dictionaryFullPath);
        
        nunicode_sqlite3_static_init(0);

        OpenDataBase(dictionaryFullPath.c_str(), &_db);
        _queryExecutor = new QueryExecutor(_db);
    }

    SearchEngineImpl::~SearchEngineImpl()
    {
        if (_db != nullptr)
            sqlite3_close(_db);
        if (_queryExecutor != nullptr)
            delete _queryExecutor;
    }

    void SearchEngineImpl::Search(const char *word)
    {
        _queryExecutor->Search(word);
    }

    vector<string> SearchEngineImpl::GetResult()
    {
        return _queryExecutor->GetLastSearchResult();
    }

    map<string, vector<string>> SearchEngineImpl::GetTranslate(int wordId)
    {
        map<string, vector<string>> result;

        return result;
    }

    void SearchEngineImpl::ValidateDbPath(string fullPath) const
    {
        if (fullPath.size() == 0)
        {
            throw Exception::InvalidDbPathException(fullPath);
        }
    }

    void SearchEngineImpl::OpenDataBase(const char *dbPath, sqlite3 **database)
    {
        int rv = sqlite3_open(dbPath, database);
        if (rv)
        {
            throw Exception::OpenDbException(sqlite3_errmsg(*database));
        }
    }
}