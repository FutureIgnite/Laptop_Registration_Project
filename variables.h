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
} Entries;

//...macros...
#define REG_OK 0
#define REG_ERR 1

//....function declarations...
Entries* check_if_exists (const char*); //should be implemented
int register_student (Entries*);
int register_laptop (Entries*);
void init_current_date (Entries* entry);
void init_current_date ();
Entries* input (char*);
struct tm* current_date();

#endif
