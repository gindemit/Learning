#pragma once
#include "SearchEngineExceptionBase.h"

namespace SearchEngine::Core::Exception
{
    class QueryExecException : public SearchEngineExceptionBase
    {
    public:
        explicit QueryExecException(string message) :
            SearchEngineExceptionBase("Query execution exception " + message)
        {
        }
    };
}