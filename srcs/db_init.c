#include "../includes/header_files.h"

int db_init() {

    sqlite3 *db;

    if (sqlite3_open ("laptop.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't initialize database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    fprintf(stdout, "Opened database successfully\n");
    
    // SQL to create tables
    
    sqlite3_stmt *stmt;

    const char *sql_foreign_key_enable = "PRAGMA foreign_keys = ON";
    const char *sql_st = "CREATE TABLE IF NOT EXISTS students ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "name TEXT NOT NULL,"
                                 "reg_no TEXT NOT NULL,"
                                 "phone_no TEXT NOT NULL,"
                                 "year_of_study TEXT NOT NULL,"
                                 "date_of_reg TEXT NOT NULL,"
                                 "flaged TEXT NOT NULL CHECK(flaged IN (Y, N) DEFAULT 'N';"
                               "CREATE TABLE IF NOT EXISTS laptops ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "student_id INTEGER FOREIGN KEY,"
                                 "model TEXT NOT NULL,"
                                 "serial_no TEXT NOT NULL,"
                                 "FOREIGN KEY (student_id) REFERENCES students (id) ON DELETE CASCADE);";
    const char *sqlTail;

    if (sqlite3_prepare_v2 (db, sql_st, -1, &stmt, &sqlTail) != SQLITE_OK){
        fprintf (stderr, "Error praparing statement (student_table): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return 1;
    }

    if (sqlite3_step (stmt) != SQLITE_DONE){
        fprintf (stderr, "Error executing statement (student_table): %s\n", sqlite3_errmsg (db));
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return 1;
    }
    
    sqlite3_finalize (stmt);

    if (sqlite3_prepare_v2 (db, sqlTail, -1, &stmt, NULL) != SQLITE_OK){
        fprintf (stderr, "Error preparing statement (laptops_table): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return 1;
    }

    if (sqlite3_step (stmt) != SQLITE_OK){
        fprintf (stderr, "Error executing statement (laptops_table): %s\n", sqlite3_errmsg (db));
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return 1;
    }

    sqlite3_finalize (stmt);

    if (sqlite3_prepare_v2 (db, sql_foreign_key_enable, -1, &stmt, NULL) != SQLITE_OK){
        fprintf (stderr, "Error preparing statement (foreign_key): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return 1;
    }

    if (sqlite3_step (stmt) != SQLITE_DONE){
        fprintf (stderr, "Error executing statement (foreign_keys): %s\n", sqlite3_errmsg (db));
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return 1;
    }

    sqlite3_finalize (stmt);
    sqlite3_close (db);

    return 0;
}

