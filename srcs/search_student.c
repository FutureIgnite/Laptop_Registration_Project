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

    int id;
    char *col_text;

    if (sqlite3_step (stmt) == SQLITE_ROW) {
        
        col_text =  (char *)sqlite3_column_text (stmt, 1);
        strncpy (stdnt -> student.student_name,   col_text ? col_text : "", sizeof (stdnt -> student.student_name) -1);
        //add_terminator (stdnt -> student.student_name);

        col_text =  (char *)sqlite3_column_text (stmt, 2);
        strncpy (stdnt -> student.reg_no,         col_text ? col_text : "", sizeof (stdnt -> student.reg_no) -1);
        //add_terminator (stdnt -> student.reg_no);

        col_text =  (char *)sqlite3_column_text (stmt, 3);
        strncpy (stdnt -> student.phone_no,       col_text ? col_text : "", sizeof (stdnt -> student.phone_no) -1);
        //add_terminator (stdnt -> student.phone_no);

        col_text =  (char *)sqlite3_column_text (stmt, 4);
        strncpy (stdnt -> student.y_of_study,     col_text ? col_text : "", sizeof (stdnt -> student.y_of_study) -1);
        //add_terminator (stdnt -> student.y_of_study);
        
        col_text =  (char *)sqlite3_column_text (stmt, 5);
        strncpy (stdnt -> t_stamp.t_registration,  col_text ? col_text : "", sizeof (stdnt -> t_stamp.t_registration) -1);
        //add_terminator (stdnt -> t_stamp.t_registration);
        
        id = sqlite3_column_int (stmt, 0);
    }

    sqlite3_finalize (stmt);

    const char *sql_l = "SELECT * FROM laptops WHERE student_id = (?)";

    if (sqlite3_prepare_v2 (db, sql_l, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf (stderr, "Error preparing statement (f_laptop): %s\n", sqlite3_errmsg (db));
        sqlite3_close (db);
        return NULL;
    }

    sqlite3_bind_int (stmt, 1, id);

    if (sqlite3_step (stmt) == SQLITE_ROW){
        
        col_text = (char *)sqlite3_column_text (stmt, 3);
        strncpy (stdnt -> laptop.model,           col_text ? col_text : "", sizeof (stdnt -> laptop.model) -1);
        //add_terminator (stdnt -> laptop.model);

        col_text =  (char *)sqlite3_column_text (stmt, 4);
        strncpy (stdnt -> laptop.serial_no,       col_text ? col_text : "", sizeof (stdnt -> laptop.serial_no) -1);
        //add_terminator (stdnt -> laptop.serial_no);

       
        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return stdnt;
    }

    sqlite3_close (db);
    return NULL;        

}



