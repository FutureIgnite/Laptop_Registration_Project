#include "../includes/header_files.h"


int prompt (Entry *entry) {
    int opt = 0, counter = 0; // option
    char res = 'Y', des = 'N';//response descision
    char reg_no[20];
    Entry *stdnt = NULL;
    while (des != 'Q' || des != 'q') {
        switch (opt) {
            case 1:
                do {
                    if (register_student (entry) == REG_ERR) {
                        fprintf (stderr, "Cannot register student\n");
                        break;
                    }
             
                    if (register_laptop (entry) == REG_ERR) {
                        fprintf (stderr, "Cannot register laptop\n");
                        break;
                    }

                    if (save_data (entry)) 
                        printf ("Student not saved\n");
                    else
                        printf ("Student saved successfully\n");
                    
                    printf ("Do you want to register another student? (Y/N) : ");
                    scanf ("%c", &res);
                    flush_input_buff ();
                    system ("clear");
                    ++counter;
                } while (res != 'N');
                printf ("%i students successfully registered\n", counter);
                sleep (1);
                system ("clear");
                break;
            case 0:
                do {
                    printf ("Enter students registation number: ");
                    fgets (reg_no, sizeof (reg_no), stdin);
                    add_terminator (reg_no);
                    if (!(stdnt = lookup_db (reg_no)))
                        fprintf (stderr, "Student dont exists\n");
                    else
                        display (stdnt);
                    printf ("Do you want to search for another student(Y/N): ");
                    scanf ("%c", &res);
                    flush_input_buff ();
                    system ("clear");
                } while (res != 'N');
                break;            
        }
        
        printf ("quit (Q) cancel (C): ");
        scanf ("%c", &des);
        flush_input_buff ();
    }

    return 0;
}

void display (Entry *entry){
    printf ("\n\t%s%s            STUDENT RECORD                               %s%s\n\n", 
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
