#pragma once
#include "SearchEngineExceptionBase.h"

namespace SearchEngine::Core::Exception
{
    class InvalidDbPathException : public SearchEngineExceptionBase
    {
    public:
        explicit InvalidDbPathException(const string &path) :
            SearchEngineExceptionBase("Invalid database path" + path)
        {
        }

        explicit InvalidDbPathException(const char *path) :
            SearchEngineExceptionBase("Invalid database path" + string(path))
        {
        }
    };
}