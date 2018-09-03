#ifndef _NU_WRAPPER_H_
#define _NU_WRAPPER_H_

#include "nunicode/libnu/libnu.h"

const char* toLower(unsigned int character)
{
    return nu_tolower(character);
}

const char* toUpper(unsigned int character)
{
    return nu_toupper(character);
}

#endif // _NU_WRAPPER_H_
