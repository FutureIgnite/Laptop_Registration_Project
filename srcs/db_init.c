/* Ensure C89 Standard Adhreance */

#include "../includes/header_files.h"

/**
 * db_init - Initialized the SQLite database and creates the required tables
 *
 * Return: 0 on success, 1 on failure
 */

int db_init(void)
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;

    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        printw("Can't initialize database: %s\n", sqlite3_errmsg(db)); R;
        return 1;
    }

    printw("Opened database successfully\n"); R;
    
    /* SQL Query to create database tables */

    const char *sql_foreign_key_enable = "PRAGMA foreign_keys = ON";
    const char *sql_st =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "reg_no TEXT NOT NULL, "
        "phone_no TEXT NOT NULL, "
        "year_of_study TEXT NOT NULL, "
        "date_of_reg TEXT NOT NULL, "
        "flaged TEXT NOT NULL CHECK(flaged IN ('Y','N')) DEFAULT 'N'"
        ");"
        "CREATE TABLE IF NOT EXISTS laptops ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_id INTEGER NOT NULL, "
        "model TEXT NOT NULL, "
        "serial_no TEXT NOT NULL, "
        "FOREIGN KEY (student_id) REFERENCES students (id) ON DELETE CASCADE"
        ");";

    const char *sqlTail = NULL;
    int rc = 0;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK)
    {
        printw("Error opening database: %s\n", sqlite3_errmsg(db)); R;
        return 1;
    }
    printw("Database Opened Successfully!\n"); R;

    /* Prepare student table creation */
    rc = sqlite3_prepare_v2(db, sql_st, -1, &stmt, &sqlTail);
    CHECK_SQLITE(rc, db, cleanup, "Error preparing statement (student table)");

    /* Create student table(execution) */
    rc = sqlite3_step(stmt);
    CHECK_SQLITE(rc, db, cleanup, "Error executing statement (student table)");

    sqlite3_finalize(stmt);
    stmt = NULL;

    /* Prepare laptop table */
    rc = sqlite3_prepare_v2(db, sqlTail, -1, &stmt, NULL);
    CHECK_SQLITE(rc, db, cleanup, "Error preparing statement (laptop table)");

    /* execution of laptop table query */
    rc = sqlite3_step(stmt);
    CHECK_SQLITE(rc, db, cleanup, "Error executing statement (laptop table)");

    sqlite3_finalize(stmt);
    stmt = NULL;

    /* Enable Foreign key creation */
    rc = sqlite3_prepare_v2(db, sql_foreign_key_enable, -1, &stmt, NULL);
    CHECK_SQLITE(rc, db, cleanup, "Error preparing statement (foreign keys)");
    
    rc = sqlite3_step(stmt);
    CHECK_SQLITE(rc, db, cleanup, "Error executing statement (foreign keys)");

cleanup:
    if (stmt != NULL)
    {
        sqlite3_finalize(stmt);
    }
    if (db != NULL)
    {
        sqlite3_close(db);
    }

    return (rc == SQLITE_OK || rc == SQLITE_DONE) ? 0: 1;
}

/**
 * lookup_db - Searches for a student in the database using their registration number
 * @buff: The registration number to search for
 *
 * Return: Pointer to the Entry struct containing student details, or NULL on failure
 */
Entry* lookup_db (const char *buff)
{
    Entry *stdnt = NULL;
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;

    if (!(stdnt = (Entry*) malloc (sizeof(Entry)))) {
        printw ("Error allocating memory (student object): %s\n", strerror(errno)); R;
        return NULL;
    }

    if (sqlite3_open (DATABASE, &db) != SQLITE_OK) {
        printw ("Error opening db (search): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_close (db);
        return NULL;
    }


    const char *sql = "SELECT * FROM students WHERE reg_no = (?)";

    if (sqlite3_prepare_v2 (db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printw ("Error preparing statement (search): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_close (db);
        return NULL;
    }

    sqlite3_bind_text (stmt, 1, buff, -1, SQLITE_TRANSIENT);

    int id;
    char *col_text;

    if (sqlite3_step (stmt) == SQLITE_ROW) {
        
        col_text =  (char *)sqlite3_column_text (stmt, 1);
        strncpy (stdnt -> student.student_name,   col_text ? col_text : "", sizeof (stdnt -> student.student_name) -1);

        col_text =  (char *)sqlite3_column_text (stmt, 2);
        strncpy (stdnt -> student.reg_no,         col_text ? col_text : "", sizeof (stdnt -> student.reg_no) -1);

        col_text =  (char *)sqlite3_column_text (stmt, 3);
        strncpy (stdnt -> student.phone_no,       col_text ? col_text : "", sizeof (stdnt -> student.phone_no) -1);

        col_text =  (char *)sqlite3_column_text (stmt, 4);
        strncpy (stdnt -> student.y_of_study,     col_text ? col_text : "", sizeof (stdnt -> student.y_of_study) -1);
        
        col_text =  (char *)sqlite3_column_text (stmt, 5);
        strncpy (stdnt -> t_stamp.t_registration,  col_text ? col_text : "", sizeof (stdnt -> t_stamp.t_registration) -1);
        
        id = sqlite3_column_int (stmt, 0);
    }

    sqlite3_finalize (stmt);

    const char *sql_l = "SELECT * FROM laptops WHERE student_id = (?)";

    if (sqlite3_prepare_v2 (db, sql_l, -1, &stmt, NULL) != SQLITE_OK) {
        printw ("Error preparing statement (f_laptop): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_close (db);
        return NULL;
    }

    sqlite3_bind_int (stmt, 1, id);

    if (sqlite3_step (stmt) == SQLITE_ROW){
        
        col_text = (char *)sqlite3_column_text (stmt, 2);
        strncpy (stdnt -> laptop.model,           col_text ? col_text : "", sizeof (stdnt -> laptop.model) -1);

        col_text =  (char *)sqlite3_column_text (stmt, 3);
        strncpy (stdnt -> laptop.serial_no,       col_text ? col_text : "", sizeof (stdnt -> laptop.serial_no) -1);

       
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return stdnt;
    }

    sqlite3_close (db);
    free (stdnt);
    return NULL;        

}   

int flag_student (const char *reg_no) {
    sqlite3 *db;
    
    if (sqlite3_open ("records.db", &db)) {
        printw ("Cannot open database (flaging): %s\n", sqlite3_errmsg (db)); R;
        return 1;
    }

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE students SET flaged = 'Y' WHERE reg_no = (?)";
    
    if (sqlite3_prepare_v2 (db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printw ("Error preparing statement (flaging): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_close (db);
        return 1;
    }

    sqlite3_bind_text (stmt, 1, reg_no, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) != SQLITE_DONE) {
        printw ("Failed to flag student: %s\n", sqlite3_errmsg (db)); R;
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return 1;
    }

    sqlite3_finalize (stmt);
    sqlite3_close (db);

    return 0;
}

int save_data (Entry *entry){
    sqlite3 *db;
    
    if (sqlite3_open ("records.db", &db) != SQLITE_OK){
        printw ("Error opening database (write_db): %s\n", sqlite3_errmsg (db)); R;
        free (entry);
        return  1;
    }

    sqlite3_stmt *stmt;
    
    const char *sql_s = "INSERT INTO students ("
        "name, reg_no, phone_no, year_of_study, date_of_reg) VALUES (?, ?, ?, ?, ?)";

    const char *sql_l = "INSERT INTO laptops (student_id, model, serial_no) VALUES (?, ?, ?)";

    if (sqlite3_prepare_v2 (db, sql_s, -1, &stmt, NULL) != SQLITE_OK) {
        printw ("Error preparing statement (write_db_s): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_close (db);
        free (entry);
        return 1;
    }

    sqlite3_bind_text (stmt, 1, entry -> student.student_name, -1,   SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 2, entry -> student.reg_no, -1,         SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 3, entry -> student.phone_no, -1,       SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 4, entry -> student.y_of_study, -1,     SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 5, entry -> t_stamp.t_registration, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) != SQLITE_DONE) {
        printw ("Error executing statement (write_db_s): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_finalize (stmt);
        sqlite3_close    (db);
        free (entry);
        return 1;
    }
    
    int student_id = sqlite3_last_insert_rowid (db);

    sqlite3_finalize (stmt);

    if (sqlite3_prepare_v2 (db, sql_l, -1, &stmt, NULL)) {
        printw ("Error preparing statement (write_db_l): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_close (db);
        free (entry);
        return 1;
    }
    
    sqlite3_bind_int  (stmt,  1, student_id);
    sqlite3_bind_text (stmt, 2, entry -> laptop.model, -1,     SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 3, entry -> laptop.serial_no, -1, SQLITE_TRANSIENT);

    if (sqlite3_step (stmt) != SQLITE_DONE){
        printw ("Error executing statement (write_db_l): %s\n", sqlite3_errmsg (db)); R;
        sqlite3_finalize (stmt);
        sqlite3_close    (db);
        free (entry);
        return 1;
    }

    sqlite3_finalize (stmt);
    
    sqlite3_close    (db);

    free (entry);
    return 0;
}
