#ifndef VARIABLES_H
#define VARIABLES_H
#include <stdlib.h>
#include <stdio.h>

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
   time_stamp t_stamp;
   laptop_details laptop;
   student_details student;
} Entry;

//...macros...
#define REG_OK 0
#define REG_ERR 1
#define create_new_screen() puts ("\033[?1049h\033[H")
#define exit_screen() puts ("\033[?1049l")

//....function declarations...
Entry* check_if_exists (const char*); //should be implemented
int register_student (Entry*);
int register_laptop (Entry*);
void init_current_date (Entry*);
Entry* input (char*);
struct tm* current_date();

#endif
