#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

sqlite3 *db;

int db_init() {
    int rc = sqlite3_open("laptop.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS LAPTOPS("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "model TEXT NOT NULL,"
                      "serail_no TEXT NOT NULL);";

    char *err_msg = NULL;

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
    return 0;
}