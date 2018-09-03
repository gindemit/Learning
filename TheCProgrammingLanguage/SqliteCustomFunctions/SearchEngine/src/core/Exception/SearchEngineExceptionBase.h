#pragma once
#include <exception>
#include <string>

namespace SearchEngine::Core::Exception
{
    using ::std::exception;
    using ::std::string;

    class SearchEngineExceptionBase : public exception
    {
    public:
        explicit SearchEngineExceptionBase(const string &message) :
            exception(message.c_str())
        {
        }

        explicit SearchEngineExceptionBase(const char *message) :
            exception(message)
        {
        }
    };
}
