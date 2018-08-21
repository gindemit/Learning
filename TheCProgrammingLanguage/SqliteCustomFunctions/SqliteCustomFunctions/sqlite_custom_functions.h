#pragma once

#define SQLITE_MAX_LIKE_PATTERN_LENGTH 50000

#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "compare_strings.h"

void cmp(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    const unsigned char *zB = sqlite3_value_text(argv[0]);
    const unsigned char *zA = sqlite3_value_text(argv[1]);
    sqlite3_result_int(context, compare_strings(zB, zA));
}
/// Creates CMP sqlite custom function. CMP (compare)
/// Usage: SELECT id, name, deel FROM woord where CMP(name, 'test')
/// This function compares two case sensetive strings
int create_sqlite_cmp_function(sqlite3 *db, ::std::ostream &errorStream)
{
    int result = sqlite3_create_function(
        db,
        "cmp",
        2,
        SQLITE_UTF8 | SQLITE_DETERMINISTIC,
        nullptr,
        cmp,
        nullptr,
        nullptr);

    if (result) {
        errorStream << "Cannot create cmp function in database: " << sqlite3_errstr(result);
        return 1;
    }
    return 0;
}

void cmpic(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    char16_t  *zB = (char16_t*)sqlite3_value_text16(argv[0]);
    char16_t  *zA = (char16_t*)sqlite3_value_text16(argv[1]);
    sqlite3_result_int(context, compare_strings_ignore_case((unsigned short int*)zB, (unsigned short int*)zA));
}
/// Creates CMPIC sqlite custom function CMPIC (compare ignore case)
/// Usage: SELECT id, name, deel FROM woord where CMPIC(name, 'test')
/// This function compares two strings ignoring case
int create_sqlite_cmpic_function(sqlite3 *db, ::std::ostream &errorStream)
{
    int result = sqlite3_create_function(
        db,
        "cmpic",
        2,
        SQLITE_UTF16 | SQLITE_DETERMINISTIC,
        nullptr,
        cmpic,
        nullptr,
        nullptr);

    if (result) {
        errorStream << "Cannot create cmp function in database: " << sqlite3_errstr(result);
        return 1;
    }
    return 0;
}