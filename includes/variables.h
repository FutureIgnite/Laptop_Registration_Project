#ifndef VARIABLES_H
#define VARIABLES_H

typedef struct {
   char model[50];
   char serial_no[50];
} laptop_details;

typedef struct {
   char student_name[255];
   char reg_no[255];
   char phone_no[20];
   char y_of_study[20];
} student_details;

typedef struct
{
   char t_registration[50];
   char t_checkIn[50];
   char t_checkOut[50];
} time_stamp;

typedef struct
{
   time_stamp t_stamp;
   laptop_details laptop;
   student_details student;
} Entry;

/* --- Macros --- */
#define REG_OK 0
#define REG_ERR 1
#define create_new_screen() (puts("\033[?1049h\033[H"))
#define exit_screen() (puts("\033[?1049l"))
#define R refresh()
#define R2(str) wrefresh (str)
#define DATABASE "records.db"
#define CHECK_SQLITE(rc, db, label, msg) \
   do { \
      if ((rc) != SQLITE_OK && (rc) != SQLITE_DONE) { \
         printw("%s: %s\n", msg, sqlite3_errmsg(db)); \
         R; \
         sqlite3_close(db); \
         goto label; \
      } \
   } while (0)

/* Functions and utilities */
int register_student(Entry *entry, WINDOW *win);
int register_laptop(Entry *entry, WINDOW *win);
void init_current_date(Entry *entry, WINDOW *win);
void flush_input_buff(WINDOW *win);
void add_terminator(char *str, int len, int pos, WINDOW *win);
void clear_console(int flag, WINDOW *win);
int isEmpty(char c, char *str, WINDOW *win);
Entry *lookup_db(const char *filename);
void display(Entry *entry, WINDOW *win);
int prompt(Entry *entry);
int save_data(Entry *entry);
int db_init(void);
int flag_student(const char *student_id);
char guide(WINDOW *win);
int report_lost(const char *laptop_serial);
void help_method(WINDOW *win);

#endif /* VARIABLES_H */
