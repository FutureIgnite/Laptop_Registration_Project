#include "../includes/header_files.h"
    
int save_data (Entry *entry){
    sqlite3 *db;
    
    if (sqlite3_open ("records.db", &db) != SQLITE_OK){
        fprintf (stderr, "Error opening database (write_db): %s\n", sqlite3_errmsg (db));
        return  1;
    }

    sqlite3_stmt *stmt;
    
    const char *sql_s = "INSERT INTO students ("
        "name, reg_no, phone_no, year_of_study, date_of_reg) VALUES (?, ?, ?, ?, ?)";

    const char *sql_l = "INSERT INTO laptops (student_id, model, serial_no), VALUES (?, ?, ?)";

    if (sqlite3_prepare_v2 (db, sql_s, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf (stderr, "Error preparing statement (write_db_s): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return 1;
    }

    sqlite3_bind_text (stmt, 1, entry -> student.student_name, -1,   SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 2, entry -> student.reg_no, -1,         SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 3, entry -> student.phone_no, -1,       SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 4, entry -> student.y_of_study, -1,     SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 5, entry -> t_stamp.t_registration, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) != SQLITE_DONE) {
        fprintf (stderr, "Error executing statement (write_db_s): %s\n", sqlite3_errmsg (db));
        sqlite3_finalize (stmt);
        sqlite3_close    (db);
        return 1;
    }
    
    int student_id = sqlite3_last_insert_rowid (db);

    sqlite3_finalize (stmt);

    if (sqlite3_prepare_v2 (db, sql_l, -1, &stmt, NULL)) {
        fprintf (stderr, "Error preparing statement (write_db_l): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return 1;
    }
    
    sqlite3_bind_int  (stmt,  1, student_id);
    sqlite3_bind_text (stmt, 2, entry -> laptop.model, -1,     SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 3, entry -> laptop.serial_no, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) != SQLITE_DONE){
        fprintf (stderr, "Error executing statement (write_db_l): %s\n", sqlite3_errmsg (db));
        sqlite3_finalize (stmt);
        sqlite3_close    (db);
        return 1;
    }

    sqlite3_finalize (stmt);
    
    sqlite3_close    (db);

    return 0;
}


