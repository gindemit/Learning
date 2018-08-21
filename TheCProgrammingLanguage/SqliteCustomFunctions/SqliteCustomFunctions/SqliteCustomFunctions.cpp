// SqliteCustomFunctions.cpp : Defines the entry point for the console application.
//
#ifdef _WIN32
#include <Windows.h>
#define MAX_INPUT_LENGTH 1024
#endif
#include <sstream>
#include <iostream>
#include <chrono>
#include "sqlite/sqlite3.h"
//#include "sqlite_custom_functions.h"
#include "sqlite_custom_collations.h"
//#include "SqliteCustomFunctions.h"
#include "sqlite3/nusqlite3.h"

using ::std::cout;
using ::std::cin;
using ::std::endl;

::std::chrono::time_point<::std::chrono::steady_clock> start_time;

void print_elapsed_time_start()
{
    start_time = std::chrono::high_resolution_clock::now();
}
void print_elapsed_time_end()
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    std::cout << "" << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "\t|";
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    print_elapsed_time_end();

    for (int i = 0; i < argc; ++i)
    {
        cout << /*azColName[i] << " = " << */(argv[i] ? argv[i] : "NULL") << "|";
    }
    cout << endl;
    return 0;
}

void ExecuteQuery(sqlite3 *db, const char* query)
{
    char *errMsg;
    print_elapsed_time_start();
    int rv = sqlite3_exec(db, query, callback, nullptr, &errMsg);
    if (rv != SQLITE_OK)
    {
        cout << "Error: " << errMsg << endl;
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    setvbuf(stdin, nullptr, _IOFBF, 1000);

    wchar_t wstr[MAX_INPUT_LENGTH];
    char utf_result[MAX_INPUT_LENGTH * 3 + 1];

    unsigned long read;
    void *con = GetStdHandle(STD_INPUT_HANDLE);
#endif

    nunicode_sqlite3_static_init(0);
    print_elapsed_time_start();
    sqlite3 *db;
    int rv = sqlite3_open("ru_de_dict.db", &db);
    if (rv)
    {
        cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    /*create_sqlite_cmp_function(db, cout);
    create_sqlite_cmpic_function(db, cout);*/
    //create_sqlite_nocase_collating(db, cout);

    do
    {
        print_elapsed_time_end();
        cout << "Enter query:" << endl;

#ifdef _WIN32
        ReadConsole(con, wstr, MAX_INPUT_LENGTH, &read, NULL);

        int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, utf_result, sizeof(utf_result), NULL, NULL);
        utf_result[size - 2] = 0;// eat the \r\n characters at end of the string
        ::std::string query(utf_result);
#else
        ::std::string query;
        getline(cin, query);
#endif
        if (query == "q")
        {
            break;
        }
        ExecuteQuery(db, query.c_str());
    } while (true);

    sqlite3_close(db);
    return 0;
}

