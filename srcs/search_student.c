#include "../includes/header_files.h"


//lookup in the database for the object

Entry* lookup_db (const char *buff) {
    Entry *stdnt;

    if (!(stdnt = (Entry*) malloc (sizeof(Entry)))) {
        fprintf (stderr, "Error allocating memory (student object): %s\n", strerror(errno));
        return NULL;
    }

    sqlite3 *db;

    if (sqlite3_open ("records.db", &db) != SQLITE_OK) {
        fprintf (stderr, "Error opening db (search): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return NULL;
    }

    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM students WHERE reg_no = (?)";

    if (sqlite3_prepare_v2 (db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf (stderr, "Error preparing statement (search): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return NULL;
    }

    sqlite3_bind_text (stmt, 1, buff, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) == SQLITE_ROW) {
        strcpy (stdnt -> student.student_name,   (char *)sqlite3_column_text (stmt, 2));
        strcpy (stdnt -> student.reg_no,         (char *)sqlite3_column_text (stmt, 3));
        strcpy (stdnt -> student.phone_no,       (char *)sqlite3_column_text (stmt, 4));
        strcpy (stdnt -> student.y_of_study,     (char *)sqlite3_column_text (stmt, 5));

        strcpy (stdnt -> laptop.model,           (char *)sqlite3_column_text (stmt, 6));
        strcpy (stdnt -> laptop.serial_no,       (char *)sqlite3_column_text (stmt, 7));

        strcpy (stdnt -> t_stamp.t_registration, (char *)sqlite3_column_text (stmt, 8));
        
        return stdnt;
    }

    sqlite3_close (db);
    return NULL;        

}



