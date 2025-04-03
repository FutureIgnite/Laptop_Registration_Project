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

/*typedef struct {
    Laptop* Lap_Entries[1000];
} L_BUCKET;

typedef struct {
   Student* Snt_Entries[1000];
} S_BUCKET;

typedef struct {
   Time* Tm_Entries[1000];
} T_BUCKET;
*/
typedef struct {
   time_stamp t_stamp;
   laptop_details laptop;
   student_details student;
} Entries;

#define REG_OK 0
#define REG_ERR 1
int register_student (Entries*);
int register_laptop (Entries*);
void init_current_date ();
struct tm* current_date();
#endif
