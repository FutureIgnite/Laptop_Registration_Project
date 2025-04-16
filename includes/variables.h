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

typedef struct { 
   char t_registration[50]; 
   char t_checkIn[50];
   char t_checkOut[50];
} time_stamp;

typedef struct {
   time_stamp      t_stamp;
   laptop_details  laptop;
   student_details student;
} Entry;

//...macros...
#define REG_OK  0
#define REG_ERR 1
#define create_new_screen() puts ("\033[?1049h\033[H")
#define exit_screen()       puts ("\033[?1049l")

//....function declarations...
int register_student   (Entry*, WINDOW *);
int register_laptop    (Entry*, WINDOW *);
void init_current_date (Entry*, WINDOW *);
void flush_input_buff  (WINDOW *);
void add_terminator    (char*, int, int, WINDOW *);
void clear_console     (int, WINDOW *);
bool isEmpty           (char, char*, WINDOW *);
Entry* lookup_db       (const char*);
void display           (Entry *entry, WINDOW *);
int prompt             (Entry*);
int save_data          (Entry*);
int db_init            ();
int flag_student       (const char*);
char guide             (WINDOW *);
int report_lost        (const char *);
void help_method       (WINDOW *);

#endif
