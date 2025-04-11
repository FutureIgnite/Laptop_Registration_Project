
#include "../includes/header_files.h"


int flag_student (const char *reg_no) {
    sqlite3 *db;
    
    if (sqlite3_open ("records.db", &db)) {
        fprintf (stderr, "Cannot open database (flaging): %s\n", sqlite3_errmsg (db));
        return 1;
    }

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE students SET flaged = 'Y' WHERE reg_no = (?)";
    
    if (sqlite3_prepare_v2 (db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf (stderr, "Error preparing statement (flaging): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return 1;
    }

    sqlite3_bind_text (stmt, 1, reg_no, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) != SQLITE_DONE) {
        fprintf (stderr, "Failed to flag student: %s\n", sqlite3_errmsg (db));
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return 1;
    }

    sqlite3_finalize (stmt);
    sqlite3_close (db);

    return 0;
}
