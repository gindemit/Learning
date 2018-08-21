#pragma once

#include <iostream>
#include "sqlite/sqlite3.h"
#include "compare_strings.h"

int custom_strnicmp(const char16_t *zLeft, const char16_t *zRight, int N) {
    register const char16_t *a, *b;
    if (zLeft == 0) {
        return zRight ? -1 : 0;
    }
    else if (zRight == 0) {
        return 1;
    }
    a = zLeft;
    b = zRight;
    while (N-- > 0 && *a != 0 && toLower(*a) == toLower(*b)) { a++; b++; }
    return N<0 ? 0 : toLower(*a) - toLower(*b);
}

#define UNUSED_PARAMETER(x) (void)(x)

/*
** Custom collating sequence: NOCASE.
**
** This collating sequence is intended to be used for "case independent
** comparison". SQLite's knowledge of upper and lower case equivalents
** extends only to the 26 characters used in the English language.
** This function extends to the German and Cyrillic UTF-8 characters too.
**
** At the moment there is only a UTF-16 implementation.
*/
static int nocase_custom_collating_func(
    void *NotUsed,
    int nKey1, const void *pKey1,
    int nKey2, const void *pKey2
) {
    int r = custom_strnicmp(
        (const char16_t *)pKey1, (const char16_t *)pKey2, (nKey1<nKey2) ? nKey1 : nKey2);
    UNUSED_PARAMETER(NotUsed);
    if (0 == r) {
        r = nKey1 - nKey2;
    }
    return r;
}

int create_sqlite_nocase_collating(sqlite3 *db, ::std::ostream &errorStream)
{
    int result = sqlite3_create_collation(
        db,
        "NOCASE",
        SQLITE_UTF16,
        nullptr,
        nocase_custom_collating_func);

    if (result) {
        errorStream << "Can not add NOCASE collating function to database: " << sqlite3_errstr(result);
        return 1;
    }
    return 0;
}
