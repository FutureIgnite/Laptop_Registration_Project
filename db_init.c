#include <sqlite3.h>
#include "header_files.h"
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

    // SQL to create the LAPTOPS table
    const char *sql_laptops = "CREATE TABLE IF NOT EXISTS LAPTOPS("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "model TEXT NOT NULL,"
                              "serial_no TEXT NOT NULL);";

    // SQL to create the STUDENTS table
    const char *sql_students = "CREATE TABLE IF NOT EXISTS STUDENTS("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "name TEXT NOT NULL,"
                               "reg_no TEXT NOT NULL,"
                               "phone_no TEXT NOT NULL,"
                               "year_of_study TEXT NOT NULL);";

    const char *sql_time_stamp = "CREATE TABLE IF NOT EXISTS TIME_STAMP("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "date_of_reg TEXT NOT NULL,"
                                "check_out TEXT NOT NULL,"
                                "check_in TEXT NOT NULL);";
    

    char *err_msg = NULL;

    // Execute SQL for LAPTOPS table
    rc = sqlite3_exec(db, sql_laptops, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error (LAPTOPS): %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    } else {
        fprintf(stdout, "LAPTOPS table created successfully\n");
    }

    // Execute SQL for STUDENTS table
    rc = sqlite3_exec(db, sql_students, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error (STUDENTS): %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    } else {
        fprintf(stdout, "STUDENTS table created successfully\n");
    }

    if ((rc = sqlite3_exec (db, sql_time_stamp, NULL, NULL, &err_msg)) != SQLITE_OK){
        fprintf (stderr, "Erro %s", err_msg);
        sqlite3_free (err_msg);
        sqlite3_close(db);
        return rc;
    }

    return 0;
}
