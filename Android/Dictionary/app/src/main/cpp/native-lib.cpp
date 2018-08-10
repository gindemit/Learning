#include <jni.h>
#include <string>
#include <android/log.h>
#include "sqlite/sqlite3.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; ++i) {
        printf("%s = %sn", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("n");
    return 0;
}

extern "C" JNIEXPORT jstring

JNICALL
Java_com_gindemit_dictionary_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    sqlite3 *db;
    int rv = sqlite3_open("/data/data/com.gindemit.dictionary/dict.db", &db);
    if (rv) {
        char msg[256];
        sprintf(msg, "Cannot open database: %sn", sqlite3_errmsg(db));
        __android_log_print(ANDROID_LOG_VERBOSE, "Dictionary", msg, 1);
        sqlite3_close(db);
    }
    char create_table[100] = "CREATE TABLE IF NOT EXISTS customers (id INTEGER PRIMARY KEY,name TEXT NOT NULL)";
    char *errMsg;
    rv = sqlite3_exec(db, create_table, callback, 0, &errMsg);
    if (rv != SQLITE_OK) {
        __android_log_print(ANDROID_LOG_VERBOSE, "Dictionary", errMsg, 1);
    }

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
