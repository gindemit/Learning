#pragma once
#include "SearchEngineExceptionBase.h"

namespace SearchEngine::Core::Exception
{
    class OpenDbException : public SearchEngineExceptionBase
    {
    public:
        explicit OpenDbException(const char *message) :
            SearchEngineExceptionBase("Open data base exception " + string(message))
        {
        }
    };
}