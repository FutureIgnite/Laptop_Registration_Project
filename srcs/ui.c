#include "../includes/header_files.h"

void guide (int *opt) {
    printf ("\n\n\t%s%s                    CHOOSE OPERATION                       %s%s\n\n", 
             TC_CYN, TC_BG_WHT, TC_NRM, TC_BG_NRM);

    printf ("\t\t0 :  AUTHENTICATE STUDENT\n");
    printf ("\t\t1 :  REGISTER STUDENT\n");
    printf ("\n\t\t     CHOISE (0 or 1): ");
    scanf ("%d", &(*opt));
    flush_input_buff ();
}

int prompt (Entry *entry) {
    int opt = 0, counter = 0; // option
    char res, des;//response descision
    char reg_no[20];
    Entry *stdnt = NULL;

    do {
        guide ( &opt);
        switch (opt) {
            case 1:
                do {
                    if (register_student (entry) == REG_ERR) {
                        fprintf (stderr, "\t\tCannot register student\n");
                        break;
                    }
             
                    if (register_laptop (entry) == REG_ERR) {
                        fprintf (stderr, "\t\tCannot register laptop\n");
                        break;
                    }

                    if (save_data (entry)) 
                        printf ("\t\tStudent not saved\n");
                    else
                        printf ("\t\tStudent saved successfully\n");
                    
                    printf ("\t\tDo you want to register another student? (Y/N) : ");
                    scanf ("%c", &res);
                    flush_input_buff ();
                    system ("clear");
                    ++counter;
                } while (res == 'Y');
                printf ("\t\t%i students successfully registered\n", counter);
                sleep (1);
                system ("clear");
                break;
            case 0:
                do {
                    printf ("\n\n\t\tEnter students registation number: ");
                    fgets (reg_no, sizeof (reg_no), stdin);
                    add_terminator (reg_no);
                    if (!(stdnt = lookup_db (reg_no)))
                        fprintf (stderr, "\t\tStudent dont exists\n");
                    else
                        display (stdnt);
                    printf ("\t\tDo you want to search for another student(Y/N): ");
                    scanf ("%c", &res);
                    flush_input_buff ();
                    system ("clear");
                } while (res == 'Y');
                break;            
        }
        
        printf ("\t\tQuit (Q) Continue (C): ");
        scanf ("%c", &des);
        flush_input_buff ();
    }
    while (des == 'C' || des == 'c');

    return 0;
}

void display (Entry *entry){
    printf ("\n\n\t%s%s            STUDENT RECORD                               %s%s\n\n", 
              TC_CYN, TC_BG_WHT, TC_NRM, TC_BG_NRM);
    printf ("\t\tstudent name            : %s\n", entry->student.student_name);
    printf ("\t\tstdudent reg number     : %s\n", entry->student.reg_no);
    printf ("\t\tstudent phone number    : %s\n", entry->student.phone_no);
    printf ("\t\tstudent year of study   : %s\n", entry->student.y_of_study);
    
    if (strcmp (entry->t_stamp.t_registration, "NULL"))
        printf ("\t\tdate of registration    : %s\n", entry->t_stamp.t_registration);
    else
        fprintf (stderr, "\t\tDate of registration not set\n");
    
    printf ("\t\tlaptop model            : %s\n", entry->laptop.model);
    printf ("\t\tlaptop serial number    : %s\n", entry->laptop.serial_no);
    printf ("\n\t%s%s                                                         %s%s\n\n",
              TC_CYN, TC_BG_WHT, TC_NRM, TC_BG_NRM);
}
